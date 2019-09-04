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
struct vpfe_device {scalar_t__ field_off; int /*<<< orphan*/  cur_frm; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setfbaddr ) (unsigned long) ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 TYPE_2__* ccdc_dev ; 
 int /*<<< orphan*/  stub1 (unsigned long) ; 
 unsigned long videobuf_to_dma_contig (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpfe_schedule_bottom_field(struct vpfe_device *vpfe_dev)
{
	unsigned long addr;

	addr = videobuf_to_dma_contig(vpfe_dev->cur_frm);
	addr += vpfe_dev->field_off;
	ccdc_dev->hw_ops.setfbaddr(addr);
}