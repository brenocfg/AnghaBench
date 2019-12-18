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
typedef  int u32 ;
struct vbg_dev {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int VMMDEV_MOUSE_GUEST_CAN_ABSOLUTE ; 
 int VMMDEV_MOUSE_NEW_PROTOCOL ; 
 struct vbg_dev* input_get_drvdata (struct input_dev*) ; 
 int vbg_core_set_mouse_status (struct vbg_dev*,int) ; 

__attribute__((used)) static int vbg_input_open(struct input_dev *input)
{
	struct vbg_dev *gdev = input_get_drvdata(input);
	u32 feat = VMMDEV_MOUSE_GUEST_CAN_ABSOLUTE | VMMDEV_MOUSE_NEW_PROTOCOL;
	int ret;

	ret = vbg_core_set_mouse_status(gdev, feat);
	if (ret)
		return ret;

	return 0;
}