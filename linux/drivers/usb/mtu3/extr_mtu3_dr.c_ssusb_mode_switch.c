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
struct otg_switch_mtk {int dummy; } ;
struct ssusb_mtk {struct otg_switch_mtk otg_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTU3_DR_FORCE_DEVICE ; 
 int /*<<< orphan*/  MTU3_DR_FORCE_HOST ; 
 int /*<<< orphan*/  MTU3_ID_FLOAT ; 
 int /*<<< orphan*/  MTU3_ID_GROUND ; 
 int /*<<< orphan*/  MTU3_VBUS_OFF ; 
 int /*<<< orphan*/  MTU3_VBUS_VALID ; 
 int /*<<< orphan*/  ssusb_set_force_mode (struct ssusb_mtk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssusb_set_mailbox (struct otg_switch_mtk*,int /*<<< orphan*/ ) ; 

void ssusb_mode_switch(struct ssusb_mtk *ssusb, int to_host)
{
	struct otg_switch_mtk *otg_sx = &ssusb->otg_switch;

	if (to_host) {
		ssusb_set_force_mode(ssusb, MTU3_DR_FORCE_HOST);
		ssusb_set_mailbox(otg_sx, MTU3_VBUS_OFF);
		ssusb_set_mailbox(otg_sx, MTU3_ID_GROUND);
	} else {
		ssusb_set_force_mode(ssusb, MTU3_DR_FORCE_DEVICE);
		ssusb_set_mailbox(otg_sx, MTU3_ID_FLOAT);
		ssusb_set_mailbox(otg_sx, MTU3_VBUS_VALID);
	}
}