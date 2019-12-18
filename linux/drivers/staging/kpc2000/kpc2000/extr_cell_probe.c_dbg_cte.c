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
struct kp2000_device {TYPE_1__* pdev; } ;
struct core_table_entry {int offset; int length; int s2c_dma_channel_num; int c2s_dma_channel_num; int /*<<< orphan*/  irq_base_num; int /*<<< orphan*/  irq_count; scalar_t__ c2s_dma_present; scalar_t__ s2c_dma_present; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void dbg_cte(struct kp2000_device *pcard, struct core_table_entry *cte)
{
	dev_dbg(&pcard->pdev->dev, "CTE: type:%3d  offset:%3d (%3d)  length:%3d (%3d)  s2c:%d  c2s:%d  irq_count:%d  base_irq:%d\n",
		cte->type,
		cte->offset,
		cte->offset / 4096,
		cte->length,
		cte->length / 8,
		(cte->s2c_dma_present ? cte->s2c_dma_channel_num : -1),
		(cte->c2s_dma_present ? cte->c2s_dma_channel_num : -1),
		cte->irq_count,
		cte->irq_base_num
	);
}