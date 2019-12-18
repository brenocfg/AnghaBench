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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  page; } ;
struct hfa384x {scalar_t__ dlstate; int /*<<< orphan*/  dltimeout; TYPE_1__ bufinfo; scalar_t__* port_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HFA384x_DLSTATE_DISABLED ; 
 scalar_t__ HFA384x_DLSTATE_FLASHENABLED ; 
 int HFA384x_PORTID_MAX ; 
 int /*<<< orphan*/  HFA384x_RID_DOWNLOADBUFFER ; 
 int /*<<< orphan*/  HFA384x_RID_MAXLOADTIME ; 
 int hfa384x_drvr_getconfig (struct hfa384x*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int hfa384x_drvr_getconfig16 (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int hfa384x_drvr_flashdl_enable(struct hfa384x *hw)
{
	int result = 0;
	int i;

	/* Check that a port isn't active */
	for (i = 0; i < HFA384x_PORTID_MAX; i++) {
		if (hw->port_enabled[i]) {
			pr_debug("called when port enabled.\n");
			return -EINVAL;
		}
	}

	/* Check that we're not already in a download state */
	if (hw->dlstate != HFA384x_DLSTATE_DISABLED)
		return -EINVAL;

	/* Retrieve the buffer loc&size and timeout */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_DOWNLOADBUFFER,
					&hw->bufinfo, sizeof(hw->bufinfo));
	if (result)
		return result;

	le16_to_cpus(&hw->bufinfo.page);
	le16_to_cpus(&hw->bufinfo.offset);
	le16_to_cpus(&hw->bufinfo.len);
	result = hfa384x_drvr_getconfig16(hw, HFA384x_RID_MAXLOADTIME,
					  &hw->dltimeout);
	if (result)
		return result;

	le16_to_cpus(&hw->dltimeout);

	pr_debug("flashdl_enable\n");

	hw->dlstate = HFA384x_DLSTATE_FLASHENABLED;

	return result;
}