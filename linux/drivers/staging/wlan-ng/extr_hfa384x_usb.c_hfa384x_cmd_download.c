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
typedef  void* u16 ;
struct hfa384x_metacmd {int cmd; void* parm2; void* parm1; void* parm0; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_CMDCODE_DOWNLD ; 
 int HFA384x_CMD_CMDCODE_SET (int /*<<< orphan*/ ) ; 
 int HFA384x_CMD_PROGMODE_SET (void*) ; 
 int hfa384x_docmd (struct hfa384x*,struct hfa384x_metacmd*) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,void*,void*,void*) ; 

int hfa384x_cmd_download(struct hfa384x *hw, u16 mode, u16 lowaddr,
			 u16 highaddr, u16 codelen)
{
	struct hfa384x_metacmd cmd;

	pr_debug("mode=%d, lowaddr=0x%04x, highaddr=0x%04x, codelen=%d\n",
		 mode, lowaddr, highaddr, codelen);

	cmd.cmd = (HFA384x_CMD_CMDCODE_SET(HFA384x_CMDCODE_DOWNLD) |
		   HFA384x_CMD_PROGMODE_SET(mode));

	cmd.parm0 = lowaddr;
	cmd.parm1 = highaddr;
	cmd.parm2 = codelen;

	return hfa384x_docmd(hw, &cmd);
}