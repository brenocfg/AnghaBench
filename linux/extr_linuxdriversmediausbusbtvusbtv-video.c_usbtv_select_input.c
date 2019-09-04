#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ u16 ;
struct usbtv {int input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__ const**) ; 
 int EINVAL ; 
#define  USBTV_BASE 130 
#define  USBTV_COMPOSITE_INPUT 129 
#define  USBTV_SVIDEO_INPUT 128 
 int usbtv_set_regs (struct usbtv*,TYPE_1__ const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtv_select_input(struct usbtv *usbtv, int input)
{
	int ret;

	static const u16 composite[][2] = {
		{ USBTV_BASE + 0x0105, 0x0060 },
		{ USBTV_BASE + 0x011f, 0x00f2 },
		{ USBTV_BASE + 0x0127, 0x0060 },
		{ USBTV_BASE + 0x00ae, 0x0010 },
		{ USBTV_BASE + 0x0239, 0x0060 },
	};

	static const u16 svideo[][2] = {
		{ USBTV_BASE + 0x0105, 0x0010 },
		{ USBTV_BASE + 0x011f, 0x00ff },
		{ USBTV_BASE + 0x0127, 0x0060 },
		{ USBTV_BASE + 0x00ae, 0x0030 },
		{ USBTV_BASE + 0x0239, 0x0060 },
	};

	switch (input) {
	case USBTV_COMPOSITE_INPUT:
		ret = usbtv_set_regs(usbtv, composite, ARRAY_SIZE(composite));
		break;
	case USBTV_SVIDEO_INPUT:
		ret = usbtv_set_regs(usbtv, svideo, ARRAY_SIZE(svideo));
		break;
	default:
		ret = -EINVAL;
	}

	if (!ret)
		usbtv->input = input;

	return ret;
}