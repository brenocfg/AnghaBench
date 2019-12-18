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
typedef  int u8 ;
struct ucsi_connector {struct typec_altmode** partner_altmode; struct typec_altmode** port_altmode; } ;
struct typec_altmode {scalar_t__ svid; } ;

/* Variables and functions */
#define  UCSI_RECIPIENT_CON 129 
#define  UCSI_RECIPIENT_SOP 128 
 scalar_t__ USB_TYPEC_DP_SID ; 
 scalar_t__ USB_TYPEC_NVIDIA_VLINK_SID ; 
 struct typec_altmode* typec_altmode_get_partner (struct typec_altmode*) ; 
 int /*<<< orphan*/  typec_unregister_altmode (struct typec_altmode*) ; 
 int /*<<< orphan*/  ucsi_displayport_remove_partner (void*) ; 

__attribute__((used)) static void ucsi_unregister_altmodes(struct ucsi_connector *con, u8 recipient)
{
	const struct typec_altmode *pdev;
	struct typec_altmode **adev;
	int i = 0;

	switch (recipient) {
	case UCSI_RECIPIENT_CON:
		adev = con->port_altmode;
		break;
	case UCSI_RECIPIENT_SOP:
		adev = con->partner_altmode;
		break;
	default:
		return;
	}

	while (adev[i]) {
		if (recipient == UCSI_RECIPIENT_SOP &&
		    (adev[i]->svid == USB_TYPEC_DP_SID ||
			adev[i]->svid == USB_TYPEC_NVIDIA_VLINK_SID)) {
			pdev = typec_altmode_get_partner(adev[i]);
			ucsi_displayport_remove_partner((void *)pdev);
		}
		typec_unregister_altmode(adev[i]);
		adev[i++] = NULL;
	}
}