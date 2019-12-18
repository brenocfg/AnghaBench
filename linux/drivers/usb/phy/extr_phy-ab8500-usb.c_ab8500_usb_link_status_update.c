#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier; TYPE_1__* otg; } ;
struct ab8500_usb {scalar_t__ previous_link_status_state; TYPE_2__ phy; int /*<<< orphan*/  vbus_draw; int /*<<< orphan*/  mode; int /*<<< orphan*/  dev; } ;
typedef  enum ux500_musb_vbus_id_status { ____Placeholder_ux500_musb_vbus_id_status } ux500_musb_vbus_id_status ;
typedef  enum ab8500_usb_link_status { ____Placeholder_ab8500_usb_link_status } ab8500_usb_link_status ;
struct TYPE_3__ {int default_a; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTG_STATE_B_IDLE ; 
 int /*<<< orphan*/  USB_DEDICATED_CHG ; 
 int /*<<< orphan*/  USB_EVENT_CHARGER ; 
 int /*<<< orphan*/  USB_EVENT_ENUMERATED ; 
 int /*<<< orphan*/  USB_EVENT_NONE ; 
 int /*<<< orphan*/  USB_HOST ; 
 int /*<<< orphan*/  USB_IDLE ; 
#define  USB_LINK_ACA_RID_A_8500 143 
#define  USB_LINK_ACA_RID_B_8500 142 
#define  USB_LINK_ACA_RID_C_HS_8500 141 
#define  USB_LINK_ACA_RID_C_HS_CHIRP_8500 140 
#define  USB_LINK_ACA_RID_C_NM_8500 139 
#define  USB_LINK_DEDICATED_CHG_8500 138 
#define  USB_LINK_HM_IDGND_8500 137 
#define  USB_LINK_HOST_CHG_HS_8500 136 
#define  USB_LINK_HOST_CHG_HS_CHIRP_8500 135 
#define  USB_LINK_HOST_CHG_NM_8500 134 
#define  USB_LINK_NOT_CONFIGURED_8500 133 
#define  USB_LINK_NOT_VALID_LINK_8500 132 
#define  USB_LINK_RESERVED_8500 131 
#define  USB_LINK_STD_HOST_C_NS_8500 130 
#define  USB_LINK_STD_HOST_C_S_8500 129 
#define  USB_LINK_STD_HOST_NC_8500 128 
 int /*<<< orphan*/  USB_PERIPHERAL ; 
 int UX500_MUSB_CHARGER ; 
 int UX500_MUSB_ID ; 
 int UX500_MUSB_NONE ; 
 int UX500_MUSB_PREPARE ; 
 int UX500_MUSB_RIDA ; 
 int UX500_MUSB_RIDB ; 
 int UX500_MUSB_RIDC ; 
 int UX500_MUSB_VBUS ; 
 int /*<<< orphan*/  ab8500_usb_host_phy_en (struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_peri_phy_en (struct ab8500_usb*) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_phy_set_event (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_usb_link_status_update(struct ab8500_usb *ab,
		enum ab8500_usb_link_status lsts)
{
	enum ux500_musb_vbus_id_status event = 0;

	dev_dbg(ab->dev, "ab8500_usb_link_status_update %d\n", lsts);

	/*
	 * Spurious link_status interrupts are seen in case of a
	 * disconnection of a device in IDGND and RIDA stage
	 */
	if (ab->previous_link_status_state == USB_LINK_HM_IDGND_8500 &&
			(lsts == USB_LINK_STD_HOST_C_NS_8500 ||
			 lsts == USB_LINK_STD_HOST_NC_8500))
		return 0;

	if (ab->previous_link_status_state == USB_LINK_ACA_RID_A_8500 &&
			lsts == USB_LINK_STD_HOST_NC_8500)
		return 0;

	ab->previous_link_status_state = lsts;

	switch (lsts) {
	case USB_LINK_ACA_RID_B_8500:
		event = UX500_MUSB_RIDB;
		/* Fall through */
	case USB_LINK_NOT_CONFIGURED_8500:
	case USB_LINK_NOT_VALID_LINK_8500:
		ab->mode = USB_IDLE;
		ab->phy.otg->default_a = false;
		ab->vbus_draw = 0;
		if (event != UX500_MUSB_RIDB)
			event = UX500_MUSB_NONE;
		/* Fallback to default B_IDLE as nothing is connected */
		ab->phy.otg->state = OTG_STATE_B_IDLE;
		usb_phy_set_event(&ab->phy, USB_EVENT_NONE);
		break;

	case USB_LINK_ACA_RID_C_NM_8500:
	case USB_LINK_ACA_RID_C_HS_8500:
	case USB_LINK_ACA_RID_C_HS_CHIRP_8500:
		event = UX500_MUSB_RIDC;
		/* Fall through */
	case USB_LINK_STD_HOST_NC_8500:
	case USB_LINK_STD_HOST_C_NS_8500:
	case USB_LINK_STD_HOST_C_S_8500:
	case USB_LINK_HOST_CHG_NM_8500:
	case USB_LINK_HOST_CHG_HS_8500:
	case USB_LINK_HOST_CHG_HS_CHIRP_8500:
		if (ab->mode == USB_IDLE) {
			ab->mode = USB_PERIPHERAL;
			ab8500_usb_peri_phy_en(ab);
			atomic_notifier_call_chain(&ab->phy.notifier,
					UX500_MUSB_PREPARE, &ab->vbus_draw);
			usb_phy_set_event(&ab->phy, USB_EVENT_ENUMERATED);
		}
		if (event != UX500_MUSB_RIDC)
			event = UX500_MUSB_VBUS;
		break;

	case USB_LINK_ACA_RID_A_8500:
		event = UX500_MUSB_RIDA;
		/* Fall through */
	case USB_LINK_HM_IDGND_8500:
		if (ab->mode == USB_IDLE) {
			ab->mode = USB_HOST;
			ab8500_usb_host_phy_en(ab);
			atomic_notifier_call_chain(&ab->phy.notifier,
					UX500_MUSB_PREPARE, &ab->vbus_draw);
		}
		ab->phy.otg->default_a = true;
		if (event != UX500_MUSB_RIDA)
			event = UX500_MUSB_ID;
		atomic_notifier_call_chain(&ab->phy.notifier,
				event, &ab->vbus_draw);
		break;

	case USB_LINK_DEDICATED_CHG_8500:
		ab->mode = USB_DEDICATED_CHG;
		event = UX500_MUSB_CHARGER;
		atomic_notifier_call_chain(&ab->phy.notifier,
				event, &ab->vbus_draw);
		usb_phy_set_event(&ab->phy, USB_EVENT_CHARGER);
		break;

	case USB_LINK_RESERVED_8500:
		break;
	}

	return 0;
}