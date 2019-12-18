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
struct v4l2_ctrl {unsigned int ncontrols; int flags; int has_volatiles; struct v4l2_ctrl** cluster; } ;

/* Variables and functions */
 int V4L2_CTRL_FLAG_VOLATILE ; 
 scalar_t__ WARN_ON (int) ; 

void v4l2_ctrl_cluster(unsigned ncontrols, struct v4l2_ctrl **controls)
{
	bool has_volatiles = false;
	int i;

	/* The first control is the master control and it must not be NULL */
	if (WARN_ON(ncontrols == 0 || controls[0] == NULL))
		return;

	for (i = 0; i < ncontrols; i++) {
		if (controls[i]) {
			controls[i]->cluster = controls;
			controls[i]->ncontrols = ncontrols;
			if (controls[i]->flags & V4L2_CTRL_FLAG_VOLATILE)
				has_volatiles = true;
		}
	}
	controls[0]->has_volatiles = has_volatiles;
}