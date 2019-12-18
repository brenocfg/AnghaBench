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
typedef  int /*<<< orphan*/  u8 ;
struct usb_interface {int num_altsetting; TYPE_2__* cur_altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bAlternateSetting; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_NCM_COMM_ALTSETTING_MBIM ; 
 int /*<<< orphan*/  CDC_NCM_COMM_ALTSETTING_NCM ; 
 scalar_t__ cdc_ncm_comm_intf_is_mbim (struct usb_host_interface*) ; 
 scalar_t__ prefer_mbim ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 

u8 cdc_ncm_select_altsetting(struct usb_interface *intf)
{
	struct usb_host_interface *alt;

	/* The MBIM spec defines a NCM compatible default altsetting,
	 * which we may have matched:
	 *
	 *  "Functions that implement both NCM 1.0 and MBIM (an
	 *   “NCM/MBIM function”) according to this recommendation
	 *   shall provide two alternate settings for the
	 *   Communication Interface.  Alternate setting 0, and the
	 *   associated class and endpoint descriptors, shall be
	 *   constructed according to the rules given for the
	 *   Communication Interface in section 5 of [USBNCM10].
	 *   Alternate setting 1, and the associated class and
	 *   endpoint descriptors, shall be constructed according to
	 *   the rules given in section 6 (USB Device Model) of this
	 *   specification."
	 */
	if (intf->num_altsetting < 2)
		return intf->cur_altsetting->desc.bAlternateSetting;

	if (prefer_mbim) {
		alt = usb_altnum_to_altsetting(intf, CDC_NCM_COMM_ALTSETTING_MBIM);
		if (alt && cdc_ncm_comm_intf_is_mbim(alt))
			return CDC_NCM_COMM_ALTSETTING_MBIM;
	}
	return CDC_NCM_COMM_ALTSETTING_NCM;
}