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
struct omapfb_device {TYPE_1__* ctrl; } ;
struct omapfb_color_key {int dummy; } ;
struct TYPE_2__ {int (* set_color_key ) (struct omapfb_color_key*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  omapfb_rqueue_lock (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (struct omapfb_device*) ; 
 int stub1 (struct omapfb_color_key*) ; 

__attribute__((used)) static int omapfb_set_color_key(struct omapfb_device *fbdev,
				struct omapfb_color_key *ck)
{
	int r;

	if (!fbdev->ctrl->set_color_key)
		return -ENODEV;

	omapfb_rqueue_lock(fbdev);
	r = fbdev->ctrl->set_color_key(ck);
	omapfb_rqueue_unlock(fbdev);

	return r;
}