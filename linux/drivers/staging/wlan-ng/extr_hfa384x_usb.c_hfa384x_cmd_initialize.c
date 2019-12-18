#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  resp2; int /*<<< orphan*/  resp1; int /*<<< orphan*/  resp0; int /*<<< orphan*/  status; } ;
struct hfa384x_metacmd {TYPE_1__ result; scalar_t__ parm2; scalar_t__ parm1; scalar_t__ parm0; int /*<<< orphan*/  cmd; } ;
struct hfa384x {int /*<<< orphan*/  link_status; scalar_t__* port_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_CMDCODE_INIT ; 
 int /*<<< orphan*/  HFA384x_LINK_NOTCONNECTED ; 
 int HFA384x_NUMPORTS_MAX ; 
 int hfa384x_docmd (struct hfa384x*,struct hfa384x_metacmd*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfa384x_cmd_initialize(struct hfa384x *hw)
{
	int result = 0;
	int i;
	struct hfa384x_metacmd cmd;

	cmd.cmd = HFA384x_CMDCODE_INIT;
	cmd.parm0 = 0;
	cmd.parm1 = 0;
	cmd.parm2 = 0;

	result = hfa384x_docmd(hw, &cmd);

	pr_debug("cmdresp.init: status=0x%04x, resp0=0x%04x, resp1=0x%04x, resp2=0x%04x\n",
		 cmd.result.status,
		 cmd.result.resp0, cmd.result.resp1, cmd.result.resp2);
	if (result == 0) {
		for (i = 0; i < HFA384x_NUMPORTS_MAX; i++)
			hw->port_enabled[i] = 0;
	}

	hw->link_status = HFA384x_LINK_NOTCONNECTED;

	return result;
}