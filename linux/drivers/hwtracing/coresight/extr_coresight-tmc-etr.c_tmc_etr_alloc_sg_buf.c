#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tmc_drvdata {TYPE_1__* csdev; } ;
struct etr_sg_table {int /*<<< orphan*/  hwaddr; } ;
struct etr_buf {struct etr_sg_table* private; int /*<<< orphan*/  mode; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETR_MODE_ETR_SG ; 
 scalar_t__ IS_ERR (struct etr_sg_table*) ; 
 struct etr_sg_table* tmc_init_etr_sg_table (struct device*,int,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int tmc_etr_alloc_sg_buf(struct tmc_drvdata *drvdata,
				struct etr_buf *etr_buf, int node,
				void **pages)
{
	struct etr_sg_table *etr_table;
	struct device *dev = &drvdata->csdev->dev;

	etr_table = tmc_init_etr_sg_table(dev, node,
					  etr_buf->size, pages);
	if (IS_ERR(etr_table))
		return -ENOMEM;
	etr_buf->hwaddr = etr_table->hwaddr;
	etr_buf->mode = ETR_MODE_ETR_SG;
	etr_buf->private = etr_table;
	return 0;
}