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
struct vb2_queue {struct fimc_lite* drv_priv; } ;
struct fimc_lite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimc_lite_active (struct fimc_lite*) ; 
 int /*<<< orphan*/  fimc_lite_stop_capture (struct fimc_lite*,int) ; 

__attribute__((used)) static void stop_streaming(struct vb2_queue *q)
{
	struct fimc_lite *fimc = q->drv_priv;

	if (!fimc_lite_active(fimc))
		return;

	fimc_lite_stop_capture(fimc, false);
}