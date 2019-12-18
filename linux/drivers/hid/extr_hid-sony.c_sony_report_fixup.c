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
struct sony_sc {int quirks; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int FUTUREMAX_DANCE_MAT ; 
 int MOTION_CONTROLLER ; 
 int PS3REMOTE ; 
 int SINO_LITE_CONTROLLER ; 
 int VAIO_RDESC_CONSTANT ; 
 struct sony_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 int* motion_fixup (struct hid_device*,int*,unsigned int*) ; 
 int* ps3remote_fixup (struct hid_device*,int*,unsigned int*) ; 

__attribute__((used)) static u8 *sony_report_fixup(struct hid_device *hdev, u8 *rdesc,
		unsigned int *rsize)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);

	if (sc->quirks & (SINO_LITE_CONTROLLER | FUTUREMAX_DANCE_MAT))
		return rdesc;

	/*
	 * Some Sony RF receivers wrongly declare the mouse pointer as a
	 * a constant non-data variable.
	 */
	if ((sc->quirks & VAIO_RDESC_CONSTANT) && *rsize >= 56 &&
	    /* usage page: generic desktop controls */
	    /* rdesc[0] == 0x05 && rdesc[1] == 0x01 && */
	    /* usage: mouse */
	    rdesc[2] == 0x09 && rdesc[3] == 0x02 &&
	    /* input (usage page for x,y axes): constant, variable, relative */
	    rdesc[54] == 0x81 && rdesc[55] == 0x07) {
		hid_info(hdev, "Fixing up Sony RF Receiver report descriptor\n");
		/* input: data, variable, relative */
		rdesc[55] = 0x06;
	}

	if (sc->quirks & MOTION_CONTROLLER)
		return motion_fixup(hdev, rdesc, rsize);

	if (sc->quirks & PS3REMOTE)
		return ps3remote_fixup(hdev, rdesc, rsize);

	return rdesc;
}