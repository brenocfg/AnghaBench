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
struct videomode {int dummy; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int EINVAL ; 
#define  VENC_MODE_NTSC 129 
#define  VENC_MODE_PAL 128 
 int venc_get_videomode (struct videomode*) ; 

__attribute__((used)) static int venc_check_timings(struct omap_dss_device *dssdev,
			      struct videomode *vm)
{
	DSSDBG("venc_check_timings\n");

	switch (venc_get_videomode(vm)) {
	case VENC_MODE_PAL:
	case VENC_MODE_NTSC:
		return 0;
	default:
		return -EINVAL;
	}
}