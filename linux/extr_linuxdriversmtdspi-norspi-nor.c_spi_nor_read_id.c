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
struct spi_nor {int (* read_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  dev; } ;
struct flash_info {scalar_t__ id_len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct flash_info const*) ; 
 int ENODEV ; 
 struct flash_info const* ERR_PTR (int) ; 
 int /*<<< orphan*/  SPINOR_OP_RDID ; 
 int SPI_NOR_MAX_ID_LEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct flash_info const* spi_nor_ids ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const struct flash_info *spi_nor_read_id(struct spi_nor *nor)
{
	int			tmp;
	u8			id[SPI_NOR_MAX_ID_LEN];
	const struct flash_info	*info;

	tmp = nor->read_reg(nor, SPINOR_OP_RDID, id, SPI_NOR_MAX_ID_LEN);
	if (tmp < 0) {
		dev_dbg(nor->dev, "error %d reading JEDEC ID\n", tmp);
		return ERR_PTR(tmp);
	}

	for (tmp = 0; tmp < ARRAY_SIZE(spi_nor_ids) - 1; tmp++) {
		info = &spi_nor_ids[tmp];
		if (info->id_len) {
			if (!memcmp(info->id, id, info->id_len))
				return &spi_nor_ids[tmp];
		}
	}
	dev_err(nor->dev, "unrecognized JEDEC id bytes: %02x, %02x, %02x\n",
		id[0], id[1], id[2]);
	return ERR_PTR(-ENODEV);
}