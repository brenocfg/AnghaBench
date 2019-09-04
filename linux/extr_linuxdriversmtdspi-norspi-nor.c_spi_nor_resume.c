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
struct spi_nor {struct device* dev; } ;
struct mtd_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct spi_nor* mtd_to_spi_nor (struct mtd_info*) ; 
 int spi_nor_init (struct spi_nor*) ; 

__attribute__((used)) static void spi_nor_resume(struct mtd_info *mtd)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	struct device *dev = nor->dev;
	int ret;

	/* re-initialize the nor chip */
	ret = spi_nor_init(nor);
	if (ret)
		dev_err(dev, "resume() failed\n");
}