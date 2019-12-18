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
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {int (* read_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; scalar_t__ spimem; int /*<<< orphan*/ * bouncebuf; } ;
struct spi_mem_op {int dummy; } ;
struct flash_info {scalar_t__ id_len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct flash_info const*) ; 
 int ENODEV ; 
 struct flash_info const* ERR_PTR (int) ; 
 int /*<<< orphan*/  SPINOR_OP_RDID ; 
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DATA_IN (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_ADDR ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_DUMMY ; 
 int /*<<< orphan*/  SPI_NOR_MAX_ID_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int spi_mem_exec_op (scalar_t__,struct spi_mem_op*) ; 
 struct flash_info const* spi_nor_ids ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct flash_info *spi_nor_read_id(struct spi_nor *nor)
{
	int			tmp;
	u8			*id = nor->bouncebuf;
	const struct flash_info	*info;

	if (nor->spimem) {
		struct spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDID, 1),
				   SPI_MEM_OP_NO_ADDR,
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_IN(SPI_NOR_MAX_ID_LEN, id, 1));

		tmp = spi_mem_exec_op(nor->spimem, &op);
	} else {
		tmp = nor->read_reg(nor, SPINOR_OP_RDID, id,
				    SPI_NOR_MAX_ID_LEN);
	}
	if (tmp < 0) {
		dev_err(nor->dev, "error %d reading JEDEC ID\n", tmp);
		return ERR_PTR(tmp);
	}

	for (tmp = 0; tmp < ARRAY_SIZE(spi_nor_ids) - 1; tmp++) {
		info = &spi_nor_ids[tmp];
		if (info->id_len) {
			if (!memcmp(info->id, id, info->id_len))
				return &spi_nor_ids[tmp];
		}
	}
	dev_err(nor->dev, "unrecognized JEDEC id bytes: %*ph\n",
		SPI_NOR_MAX_ID_LEN, id);
	return ERR_PTR(-ENODEV);
}