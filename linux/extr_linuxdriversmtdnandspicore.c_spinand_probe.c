#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spinand_device {int /*<<< orphan*/  lock; struct spi_mem* spimem; } ;
struct spi_mem {TYPE_2__* spi; } ;
struct TYPE_4__ {TYPE_3__* parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct spinand_device* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_mem_set_drvdata (struct spi_mem*,struct spinand_device*) ; 
 int /*<<< orphan*/  spinand_cleanup (struct spinand_device*) ; 
 int spinand_init (struct spinand_device*) ; 
 int /*<<< orphan*/  spinand_set_of_node (struct spinand_device*,int /*<<< orphan*/ ) ; 
 struct mtd_info* spinand_to_mtd (struct spinand_device*) ; 

__attribute__((used)) static int spinand_probe(struct spi_mem *mem)
{
	struct spinand_device *spinand;
	struct mtd_info *mtd;
	int ret;

	spinand = devm_kzalloc(&mem->spi->dev, sizeof(*spinand),
			       GFP_KERNEL);
	if (!spinand)
		return -ENOMEM;

	spinand->spimem = mem;
	spi_mem_set_drvdata(mem, spinand);
	spinand_set_of_node(spinand, mem->spi->dev.of_node);
	mutex_init(&spinand->lock);
	mtd = spinand_to_mtd(spinand);
	mtd->dev.parent = &mem->spi->dev;

	ret = spinand_init(spinand);
	if (ret)
		return ret;

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret)
		goto err_spinand_cleanup;

	return 0;

err_spinand_cleanup:
	spinand_cleanup(spinand);

	return ret;
}