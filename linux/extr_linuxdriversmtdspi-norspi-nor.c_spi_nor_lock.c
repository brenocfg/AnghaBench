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
typedef  int /*<<< orphan*/  uint64_t ;
struct spi_nor {int (* flash_lock ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_NOR_OPS_LOCK ; 
 int /*<<< orphan*/  SPI_NOR_OPS_UNLOCK ; 
 struct spi_nor* mtd_to_spi_nor (struct mtd_info*) ; 
 int spi_nor_lock_and_prep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_unlock_and_unprep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_nor_lock(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	int ret;

	ret = spi_nor_lock_and_prep(nor, SPI_NOR_OPS_LOCK);
	if (ret)
		return ret;

	ret = nor->flash_lock(nor, ofs, len);

	spi_nor_unlock_and_unprep(nor, SPI_NOR_OPS_UNLOCK);
	return ret;
}