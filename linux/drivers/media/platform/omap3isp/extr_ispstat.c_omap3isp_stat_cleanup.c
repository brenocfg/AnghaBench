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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct ispstat {int /*<<< orphan*/  recover_priv; int /*<<< orphan*/  priv; int /*<<< orphan*/  buf; int /*<<< orphan*/  ioctl_lock; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp_stat_bufs_free (struct ispstat*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void omap3isp_stat_cleanup(struct ispstat *stat)
{
	media_entity_cleanup(&stat->subdev.entity);
	mutex_destroy(&stat->ioctl_lock);
	isp_stat_bufs_free(stat);
	kfree(stat->buf);
	kfree(stat->priv);
	kfree(stat->recover_priv);
}