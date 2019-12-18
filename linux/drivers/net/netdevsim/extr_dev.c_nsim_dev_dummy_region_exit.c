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
struct nsim_dev {int /*<<< orphan*/  dummy_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_region_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nsim_dev_dummy_region_exit(struct nsim_dev *nsim_dev)
{
	devlink_region_destroy(nsim_dev->dummy_region);
}