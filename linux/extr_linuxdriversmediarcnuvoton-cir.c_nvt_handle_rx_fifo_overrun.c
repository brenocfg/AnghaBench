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
struct nvt_dev {int /*<<< orphan*/  rdev; scalar_t__ pkts; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_clear_cir_fifo (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_get_dev (struct nvt_dev*) ; 

__attribute__((used)) static void nvt_handle_rx_fifo_overrun(struct nvt_dev *nvt)
{
	dev_warn(nvt_get_dev(nvt), "RX FIFO overrun detected, flushing data!");

	nvt->pkts = 0;
	nvt_clear_cir_fifo(nvt);
	ir_raw_event_reset(nvt->rdev);
}