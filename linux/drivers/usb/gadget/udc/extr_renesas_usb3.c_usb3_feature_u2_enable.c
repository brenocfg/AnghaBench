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
typedef  int u32 ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int SSIFCMD_UDIR_U2 ; 
 int SSIFCMD_UREQ_U2 ; 
 int /*<<< orphan*/  USB3_SSIFCMD ; 
 int /*<<< orphan*/  usb3_clear_bit (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_feature_u2_enable(struct renesas_usb3 *usb3, bool enable)
{
	u32 bits = SSIFCMD_UDIR_U2 | SSIFCMD_UREQ_U2;

	/* Enables U2 if the bits of UDIR and UREQ are set to 0 */
	if (enable)
		usb3_clear_bit(usb3, bits, USB3_SSIFCMD);
	else
		usb3_set_bit(usb3, bits, USB3_SSIFCMD);
}