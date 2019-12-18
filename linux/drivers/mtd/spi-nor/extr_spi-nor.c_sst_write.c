#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_nor {int sst_write_second; void* program_opcode; int /*<<< orphan*/  dev; } ;
struct mtd_info {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 void* SPINOR_OP_AAI_WP ; 
 void* SPINOR_OP_BP ; 
 int /*<<< orphan*/  SPI_NOR_OPS_WRITE ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 struct spi_nor* mtd_to_spi_nor (struct mtd_info*) ; 
 int spi_nor_lock_and_prep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_unlock_and_unprep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int spi_nor_wait_till_ready (struct spi_nor*) ; 
 int spi_nor_write_data (struct spi_nor*,int,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  write_disable (struct spi_nor*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static int sst_write(struct mtd_info *mtd, loff_t to, size_t len,
		size_t *retlen, const u_char *buf)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	size_t actual;
	int ret;

	dev_dbg(nor->dev, "to 0x%08x, len %zd\n", (u32)to, len);

	ret = spi_nor_lock_and_prep(nor, SPI_NOR_OPS_WRITE);
	if (ret)
		return ret;

	write_enable(nor);

	nor->sst_write_second = false;

	actual = to % 2;
	/* Start write from odd address. */
	if (actual) {
		nor->program_opcode = SPINOR_OP_BP;

		/* write one byte. */
		ret = spi_nor_write_data(nor, to, 1, buf);
		if (ret < 0)
			goto sst_write_err;
		WARN(ret != 1, "While writing 1 byte written %i bytes\n",
		     (int)ret);
		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto sst_write_err;
	}
	to += actual;

	/* Write out most of the data here. */
	for (; actual < len - 1; actual += 2) {
		nor->program_opcode = SPINOR_OP_AAI_WP;

		/* write two bytes. */
		ret = spi_nor_write_data(nor, to, 2, buf + actual);
		if (ret < 0)
			goto sst_write_err;
		WARN(ret != 2, "While writing 2 bytes written %i bytes\n",
		     (int)ret);
		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto sst_write_err;
		to += 2;
		nor->sst_write_second = true;
	}
	nor->sst_write_second = false;

	write_disable(nor);
	ret = spi_nor_wait_till_ready(nor);
	if (ret)
		goto sst_write_err;

	/* Write out trailing byte if it exists. */
	if (actual != len) {
		write_enable(nor);

		nor->program_opcode = SPINOR_OP_BP;
		ret = spi_nor_write_data(nor, to, 1, buf + actual);
		if (ret < 0)
			goto sst_write_err;
		WARN(ret != 1, "While writing 1 byte written %i bytes\n",
		     (int)ret);
		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto sst_write_err;
		write_disable(nor);
		actual += 1;
	}
sst_write_err:
	*retlen += actual;
	spi_nor_unlock_and_unprep(nor, SPI_NOR_OPS_WRITE);
	return ret;
}