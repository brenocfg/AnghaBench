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
struct TYPE_4__ {int member_0; int member_1; } ;
typedef  TYPE_1__ u16 ;
struct usbtv {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  input; int /*<<< orphan*/  norm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__ const**) ; 
#define  USBTV_BASE 128 
 int usbtv_select_input (struct usbtv*,int /*<<< orphan*/ ) ; 
 int usbtv_select_norm (struct usbtv*,int /*<<< orphan*/ ) ; 
 int usbtv_set_regs (struct usbtv*,TYPE_1__ const**,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbtv_setup_capture(struct usbtv *usbtv)
{
	int ret;
	static const u16 setup[][2] = {
		/* These seem to enable the device. */
		{ USBTV_BASE + 0x0008, 0x0001 },
		{ USBTV_BASE + 0x01d0, 0x00ff },
		{ USBTV_BASE + 0x01d9, 0x0002 },

		/* These seem to influence color parameters, such as
		 * brightness, etc. */
		{ USBTV_BASE + 0x0239, 0x0040 },
		{ USBTV_BASE + 0x0240, 0x0000 },
		{ USBTV_BASE + 0x0241, 0x0000 },
		{ USBTV_BASE + 0x0242, 0x0002 },
		{ USBTV_BASE + 0x0243, 0x0080 },
		{ USBTV_BASE + 0x0244, 0x0012 },
		{ USBTV_BASE + 0x0245, 0x0090 },
		{ USBTV_BASE + 0x0246, 0x0000 },

		{ USBTV_BASE + 0x0278, 0x002d },
		{ USBTV_BASE + 0x0279, 0x000a },
		{ USBTV_BASE + 0x027a, 0x0032 },
		{ 0xf890, 0x000c },
		{ 0xf894, 0x0086 },

		{ USBTV_BASE + 0x00ac, 0x00c0 },
		{ USBTV_BASE + 0x00ad, 0x0000 },
		{ USBTV_BASE + 0x00a2, 0x0012 },
		{ USBTV_BASE + 0x00a3, 0x00e0 },
		{ USBTV_BASE + 0x00a4, 0x0028 },
		{ USBTV_BASE + 0x00a5, 0x0082 },
		{ USBTV_BASE + 0x00a7, 0x0080 },
		{ USBTV_BASE + 0x0000, 0x0014 },
		{ USBTV_BASE + 0x0006, 0x0003 },
		{ USBTV_BASE + 0x0090, 0x0099 },
		{ USBTV_BASE + 0x0091, 0x0090 },
		{ USBTV_BASE + 0x0094, 0x0068 },
		{ USBTV_BASE + 0x0095, 0x0070 },
		{ USBTV_BASE + 0x009c, 0x0030 },
		{ USBTV_BASE + 0x009d, 0x00c0 },
		{ USBTV_BASE + 0x009e, 0x00e0 },
		{ USBTV_BASE + 0x0019, 0x0006 },
		{ USBTV_BASE + 0x008c, 0x00ba },
		{ USBTV_BASE + 0x0101, 0x00ff },
		{ USBTV_BASE + 0x010c, 0x00b3 },
		{ USBTV_BASE + 0x01b2, 0x0080 },
		{ USBTV_BASE + 0x01b4, 0x00a0 },
		{ USBTV_BASE + 0x014c, 0x00ff },
		{ USBTV_BASE + 0x014d, 0x00ca },
		{ USBTV_BASE + 0x0113, 0x0053 },
		{ USBTV_BASE + 0x0119, 0x008a },
		{ USBTV_BASE + 0x013c, 0x0003 },
		{ USBTV_BASE + 0x0150, 0x009c },
		{ USBTV_BASE + 0x0151, 0x0071 },
		{ USBTV_BASE + 0x0152, 0x00c6 },
		{ USBTV_BASE + 0x0153, 0x0084 },
		{ USBTV_BASE + 0x0154, 0x00bc },
		{ USBTV_BASE + 0x0155, 0x00a0 },
		{ USBTV_BASE + 0x0156, 0x00a0 },
		{ USBTV_BASE + 0x0157, 0x009c },
		{ USBTV_BASE + 0x0158, 0x001f },
		{ USBTV_BASE + 0x0159, 0x0006 },
		{ USBTV_BASE + 0x015d, 0x0000 },
	};

	ret = usbtv_set_regs(usbtv, setup, ARRAY_SIZE(setup));
	if (ret)
		return ret;

	ret = usbtv_select_norm(usbtv, usbtv->norm);
	if (ret)
		return ret;

	ret = usbtv_select_input(usbtv, usbtv->input);
	if (ret)
		return ret;

	ret = v4l2_ctrl_handler_setup(&usbtv->ctrl);
	if (ret)
		return ret;

	return 0;
}