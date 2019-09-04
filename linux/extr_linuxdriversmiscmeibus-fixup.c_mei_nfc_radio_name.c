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
struct mei_nfc_if_version {scalar_t__ vendor_id; scalar_t__ radio_type; } ;

/* Variables and functions */
 scalar_t__ MEI_NFC_VENDOR_INSIDE ; 
 scalar_t__ MEI_NFC_VENDOR_INSIDE_UREAD ; 
 scalar_t__ MEI_NFC_VENDOR_NXP ; 
 scalar_t__ MEI_NFC_VENDOR_NXP_PN544 ; 

__attribute__((used)) static const char *mei_nfc_radio_name(struct mei_nfc_if_version *ver)
{

	if (ver->vendor_id == MEI_NFC_VENDOR_INSIDE) {
		if (ver->radio_type == MEI_NFC_VENDOR_INSIDE_UREAD)
			return "microread";
	}

	if (ver->vendor_id == MEI_NFC_VENDOR_NXP) {
		if (ver->radio_type == MEI_NFC_VENDOR_NXP_PN544)
			return "pn544";
	}

	return NULL;
}