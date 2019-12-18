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
typedef  int u16 ;
struct wusbhc {int dummy; } ;

/* Variables and functions */
#define  C_HUB_LOCAL_POWER 129 
#define  C_HUB_OVER_CURRENT 128 
 int EPIPE ; 

__attribute__((used)) static int wusbhc_rh_clear_hub_feat(struct wusbhc *wusbhc, u16 feature)
{
	int result;

	switch (feature) {
	case C_HUB_LOCAL_POWER:
		/* FIXME: maybe plug bit 0 to the power input status,
		 * if any?
		 * see wusbhc_rh_get_hub_status() */
	case C_HUB_OVER_CURRENT:
		result = 0;
		break;
	default:
		result = -EPIPE;
	}
	return result;
}