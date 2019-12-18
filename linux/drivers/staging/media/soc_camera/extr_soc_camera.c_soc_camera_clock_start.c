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
struct soc_camera_host {int /*<<< orphan*/  clk_lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* clock_start ) (struct soc_camera_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct soc_camera_host*) ; 

__attribute__((used)) static int soc_camera_clock_start(struct soc_camera_host *ici)
{
	int ret;

	if (!ici->ops->clock_start)
		return 0;

	mutex_lock(&ici->clk_lock);
	ret = ici->ops->clock_start(ici);
	mutex_unlock(&ici->clk_lock);

	return ret;
}