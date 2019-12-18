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
struct dvb_usb_device {int dummy; } ;
struct cxusb_bt656_params {int /*<<< orphan*/  fmode; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT656 ; 
 unsigned char CXUSB_BT656_SEAV_MASK ; 
 unsigned char CXUSB_BT656_SEAV_SAV ; 
 int /*<<< orphan*/  START_SEARCH ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxusb_medion_cf_refc_vbi_smpl(struct dvb_usb_device *dvbdev,
					  struct cxusb_bt656_params *bt656,
					  unsigned char buf[4])
{
	bool sav_code = (buf[3] & CXUSB_BT656_SEAV_MASK) ==
		CXUSB_BT656_SEAV_SAV;

	if (sav_code)
		cxusb_vprintk(dvbdev, BT656, "SAV in VBI samples @ pos %u\n",
			      bt656->pos);

	bt656->fmode = START_SEARCH;
}