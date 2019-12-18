#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {TYPE_1__* locking_ops; } ;
struct spi_nor {TYPE_2__ params; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {int (* is_locked ) (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_NOR_OPS_LOCK ; 
 int /*<<< orphan*/  SPI_NOR_OPS_UNLOCK ; 
 struct spi_nor* mtd_to_spi_nor (struct mtd_info*) ; 
 int spi_nor_lock_and_prep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_unlock_and_unprep (struct spi_nor*,int /*<<< orphan*/ ) ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_nor_is_locked(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	int ret;

	ret = spi_nor_lock_and_prep(nor, SPI_NOR_OPS_UNLOCK);
	if (ret)
		return ret;

	ret = nor->params.locking_ops->is_locked(nor, ofs, len);

	spi_nor_unlock_and_unprep(nor, SPI_NOR_OPS_LOCK);
	return ret;
}