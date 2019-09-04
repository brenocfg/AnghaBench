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
struct fimc_is {int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimc_isp_subdev_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fimc_is_unregister_subdevs(struct fimc_is *is)
{
	fimc_isp_subdev_destroy(&is->isp);
	return 0;
}