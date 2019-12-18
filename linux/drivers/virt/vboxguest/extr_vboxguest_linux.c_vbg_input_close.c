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
struct vbg_dev {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct vbg_dev* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  vbg_core_set_mouse_status (struct vbg_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vbg_input_close(struct input_dev *input)
{
	struct vbg_dev *gdev = input_get_drvdata(input);

	vbg_core_set_mouse_status(gdev, 0);
}