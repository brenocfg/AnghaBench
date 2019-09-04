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
struct v4l2_selection {int /*<<< orphan*/  r; } ;
struct soc_camera_device {struct sh_mobile_ceu_cam* host_priv; } ;
struct sh_mobile_ceu_cam {int /*<<< orphan*/  subrect; } ;

/* Variables and functions */

__attribute__((used)) static int sh_mobile_ceu_get_selection(struct soc_camera_device *icd,
				       struct v4l2_selection *sel)
{
	struct sh_mobile_ceu_cam *cam = icd->host_priv;

	sel->r = cam->subrect;

	return 0;
}