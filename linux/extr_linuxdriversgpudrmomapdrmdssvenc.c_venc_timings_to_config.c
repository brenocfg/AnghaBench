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
struct venc_config {int dummy; } ;

/* Variables and functions */
#define  VENC_MODE_NTSC 129 
#define  VENC_MODE_PAL 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct venc_config const venc_config_ntsc_trm ; 
 struct venc_config const venc_config_pal_trm ; 
 int venc_get_videomode (struct videomode*) ; 

__attribute__((used)) static const struct venc_config *venc_timings_to_config(struct videomode *vm)
{
	switch (venc_get_videomode(vm)) {
	default:
		WARN_ON_ONCE(1);
	case VENC_MODE_PAL:
		return &venc_config_pal_trm;
	case VENC_MODE_NTSC:
		return &venc_config_ntsc_trm;
	}
}