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
struct mei_device {int dummy; } ;
struct hbm_dma_ring_ctrl {int dummy; } ;

/* Variables and functions */
 struct hbm_dma_ring_ctrl* mei_dma_ring_ctrl (struct mei_device*) ; 
 int /*<<< orphan*/  memset (struct hbm_dma_ring_ctrl*,int /*<<< orphan*/ ,int) ; 

void mei_dma_ring_reset(struct mei_device *dev)
{
	struct hbm_dma_ring_ctrl *ctrl = mei_dma_ring_ctrl(dev);

	if (!ctrl)
		return;

	memset(ctrl, 0, sizeof(*ctrl));
}