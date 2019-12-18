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
struct komeda_dev {struct d71_dev* chip_data; } ;
struct d71_pipeline {int /*<<< orphan*/  dou_addr; } ;
struct d71_dev {struct d71_pipeline** pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_IRQ_MASK ; 
 int /*<<< orphan*/  DOU_IRQ_PL0 ; 
 int /*<<< orphan*/  malidp_write32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d71_on_off_vblank(struct komeda_dev *mdev, int master_pipe, bool on)
{
	struct d71_dev *d71 = mdev->chip_data;
	struct d71_pipeline *pipe = d71->pipes[master_pipe];

	malidp_write32_mask(pipe->dou_addr, BLK_IRQ_MASK,
			    DOU_IRQ_PL0, on ? DOU_IRQ_PL0 : 0);
}