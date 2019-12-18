#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_8__ {TYPE_3__ pixfmt; int /*<<< orphan*/  usb_err; int /*<<< orphan*/  alt; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;
struct sd {scalar_t__ bridge; scalar_t__ revision; int sensor; int clockdiv; TYPE_4__ gspca_dev; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_OV518 ; 
 scalar_t__ BRIDGE_OV518PLUS ; 
 int /*<<< orphan*/  EIO ; 
 int R51x_FIFO_PSIZE ; 
#define  SEN_OV7620 129 
#define  SEN_OV7620AE 128 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  i2c_w (struct sd*,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov518_reg_w32 (struct sd*,int,int,int) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  reg_w_mask (struct sd*,int,int,int) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov518_mode_init_regs(struct sd *sd)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int hsegs, vsegs, packet_size;
	struct usb_host_interface *alt;
	struct usb_interface *intf;

	intf = usb_ifnum_to_if(sd->gspca_dev.dev, sd->gspca_dev.iface);
	alt = usb_altnum_to_altsetting(intf, sd->gspca_dev.alt);
	if (!alt) {
		gspca_err(gspca_dev, "Couldn't get altsetting\n");
		sd->gspca_dev.usb_err = -EIO;
		return;
	}

	packet_size = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
	ov518_reg_w32(sd, R51x_FIFO_PSIZE, packet_size & ~7, 2);

	/******** Set the mode ********/
	reg_w(sd, 0x2b, 0);
	reg_w(sd, 0x2c, 0);
	reg_w(sd, 0x2d, 0);
	reg_w(sd, 0x2e, 0);
	reg_w(sd, 0x3b, 0);
	reg_w(sd, 0x3c, 0);
	reg_w(sd, 0x3d, 0);
	reg_w(sd, 0x3e, 0);

	if (sd->bridge == BRIDGE_OV518) {
		/* Set 8-bit (YVYU) input format */
		reg_w_mask(sd, 0x20, 0x08, 0x08);

		/* Set 12-bit (4:2:0) output format */
		reg_w_mask(sd, 0x28, 0x80, 0xf0);
		reg_w_mask(sd, 0x38, 0x80, 0xf0);
	} else {
		reg_w(sd, 0x28, 0x80);
		reg_w(sd, 0x38, 0x80);
	}

	hsegs = sd->gspca_dev.pixfmt.width / 16;
	vsegs = sd->gspca_dev.pixfmt.height / 4;

	reg_w(sd, 0x29, hsegs);
	reg_w(sd, 0x2a, vsegs);

	reg_w(sd, 0x39, hsegs);
	reg_w(sd, 0x3a, vsegs);

	/* Windows driver does this here; who knows why */
	reg_w(sd, 0x2f, 0x80);

	/******** Set the framerate ********/
	if (sd->bridge == BRIDGE_OV518PLUS && sd->revision == 0 &&
					      sd->sensor == SEN_OV7620AE)
		sd->clockdiv = 0;
	else
		sd->clockdiv = 1;

	/* Mode independent, but framerate dependent, regs */
	/* 0x51: Clock divider; Only works on some cams which use 2 crystals */
	reg_w(sd, 0x51, 0x04);
	reg_w(sd, 0x22, 0x18);
	reg_w(sd, 0x23, 0xff);

	if (sd->bridge == BRIDGE_OV518PLUS) {
		switch (sd->sensor) {
		case SEN_OV7620AE:
			/*
			 * HdG: 640x480 needs special handling on device
			 * revision 2, we check for device revision > 0 to
			 * avoid regressions, as we don't know the correct
			 * thing todo for revision 1.
			 *
			 * Also this likely means we don't need to
			 * differentiate between the OV7620 and OV7620AE,
			 * earlier testing hitting this same problem likely
			 * happened to be with revision < 2 cams using an
			 * OV7620 and revision 2 cams using an OV7620AE.
			 */
			if (sd->revision > 0 &&
					sd->gspca_dev.pixfmt.width == 640) {
				reg_w(sd, 0x20, 0x60);
				reg_w(sd, 0x21, 0x1f);
			} else {
				reg_w(sd, 0x20, 0x00);
				reg_w(sd, 0x21, 0x19);
			}
			break;
		case SEN_OV7620:
			reg_w(sd, 0x20, 0x00);
			reg_w(sd, 0x21, 0x19);
			break;
		default:
			reg_w(sd, 0x21, 0x19);
		}
	} else
		reg_w(sd, 0x71, 0x17);	/* Compression-related? */

	/* FIXME: Sensor-specific */
	/* Bit 5 is what matters here. Of course, it is "reserved" */
	i2c_w(sd, 0x54, 0x23);

	reg_w(sd, 0x2f, 0x80);

	if (sd->bridge == BRIDGE_OV518PLUS) {
		reg_w(sd, 0x24, 0x94);
		reg_w(sd, 0x25, 0x90);
		ov518_reg_w32(sd, 0xc4,    400, 2);	/* 190h   */
		ov518_reg_w32(sd, 0xc6,    540, 2);	/* 21ch   */
		ov518_reg_w32(sd, 0xc7,    540, 2);	/* 21ch   */
		ov518_reg_w32(sd, 0xc8,    108, 2);	/* 6ch    */
		ov518_reg_w32(sd, 0xca, 131098, 3);	/* 2001ah */
		ov518_reg_w32(sd, 0xcb,    532, 2);	/* 214h   */
		ov518_reg_w32(sd, 0xcc,   2400, 2);	/* 960h   */
		ov518_reg_w32(sd, 0xcd,     32, 2);	/* 20h    */
		ov518_reg_w32(sd, 0xce,    608, 2);	/* 260h   */
	} else {
		reg_w(sd, 0x24, 0x9f);
		reg_w(sd, 0x25, 0x90);
		ov518_reg_w32(sd, 0xc4,    400, 2);	/* 190h   */
		ov518_reg_w32(sd, 0xc6,    381, 2);	/* 17dh   */
		ov518_reg_w32(sd, 0xc7,    381, 2);	/* 17dh   */
		ov518_reg_w32(sd, 0xc8,    128, 2);	/* 80h    */
		ov518_reg_w32(sd, 0xca, 183331, 3);	/* 2cc23h */
		ov518_reg_w32(sd, 0xcb,    746, 2);	/* 2eah   */
		ov518_reg_w32(sd, 0xcc,   1750, 2);	/* 6d6h   */
		ov518_reg_w32(sd, 0xcd,     45, 2);	/* 2dh    */
		ov518_reg_w32(sd, 0xce,    851, 2);	/* 353h   */
	}

	reg_w(sd, 0x2f, 0x80);
}