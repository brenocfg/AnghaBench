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
struct mga_device {int type; } ;

/* Variables and functions */
#define  G200_EH 135 
#define  G200_EH3 134 
#define  G200_ER 133 
#define  G200_EV 132 
#define  G200_EW3 131 
#define  G200_SE_A 130 
#define  G200_SE_B 129 
#define  G200_WB 128 
 int mga_g200eh_set_plls (struct mga_device*,long) ; 
 int mga_g200er_set_plls (struct mga_device*,long) ; 
 int mga_g200ev_set_plls (struct mga_device*,long) ; 
 int mga_g200se_set_plls (struct mga_device*,long) ; 
 int mga_g200wb_set_plls (struct mga_device*,long) ; 

__attribute__((used)) static int mga_crtc_set_plls(struct mga_device *mdev, long clock)
{
	switch(mdev->type) {
	case G200_SE_A:
	case G200_SE_B:
		return mga_g200se_set_plls(mdev, clock);
		break;
	case G200_WB:
	case G200_EW3:
		return mga_g200wb_set_plls(mdev, clock);
		break;
	case G200_EV:
		return mga_g200ev_set_plls(mdev, clock);
		break;
	case G200_EH:
	case G200_EH3:
		return mga_g200eh_set_plls(mdev, clock);
		break;
	case G200_ER:
		return mga_g200er_set_plls(mdev, clock);
		break;
	}
	return 0;
}