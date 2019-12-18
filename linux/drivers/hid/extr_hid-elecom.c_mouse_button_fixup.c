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
struct hid_device {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int MOUSE_BUTTONS_MAX ; 
 int clamp (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 

__attribute__((used)) static void mouse_button_fixup(struct hid_device *hdev,
			       __u8 *rdesc, unsigned int rsize,
			       int nbuttons)
{
	if (rsize < 32 || rdesc[12] != 0x95 ||
	    rdesc[14] != 0x75 || rdesc[15] != 0x01 ||
	    rdesc[20] != 0x29 || rdesc[30] != 0x75)
		return;
	hid_info(hdev, "Fixing up Elecom mouse button count\n");
	nbuttons = clamp(nbuttons, 0, MOUSE_BUTTONS_MAX);
	rdesc[13] = nbuttons;
	rdesc[21] = nbuttons;
	rdesc[31] = MOUSE_BUTTONS_MAX - nbuttons;
}