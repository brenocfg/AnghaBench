#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {int /*<<< orphan*/  lighting; } ;
struct TYPE_2__ {int width; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cit_PacketFormat2 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_Packet_Format1 (struct gspca_dev*,int,int) ; 
 int cit_get_clock_div (struct gspca_dev*) ; 
 int cit_model1_ntries ; 
 int cit_model1_ntries2 ; 
 int /*<<< orphan*/  cit_read_reg (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cit_start_model1(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i, clock_div;

	clock_div = cit_get_clock_div(gspca_dev);
	if (clock_div < 0)
		return clock_div;

	cit_read_reg(gspca_dev, 0x0128, 1);
	cit_read_reg(gspca_dev, 0x0100, 0);
	cit_write_reg(gspca_dev, 0x01, 0x0100);	/* LED On  */
	cit_read_reg(gspca_dev, 0x0100, 0);
	cit_write_reg(gspca_dev, 0x81, 0x0100);	/* LED Off */
	cit_read_reg(gspca_dev, 0x0100, 0);
	cit_write_reg(gspca_dev, 0x01, 0x0100);	/* LED On  */
	cit_write_reg(gspca_dev, 0x01, 0x0108);

	cit_write_reg(gspca_dev, 0x03, 0x0112);
	cit_read_reg(gspca_dev, 0x0115, 0);
	cit_write_reg(gspca_dev, 0x06, 0x0115);
	cit_read_reg(gspca_dev, 0x0116, 0);
	cit_write_reg(gspca_dev, 0x44, 0x0116);
	cit_read_reg(gspca_dev, 0x0116, 0);
	cit_write_reg(gspca_dev, 0x40, 0x0116);
	cit_read_reg(gspca_dev, 0x0115, 0);
	cit_write_reg(gspca_dev, 0x0e, 0x0115);
	cit_write_reg(gspca_dev, 0x19, 0x012c);

	cit_Packet_Format1(gspca_dev, 0x00, 0x1e);
	cit_Packet_Format1(gspca_dev, 0x39, 0x0d);
	cit_Packet_Format1(gspca_dev, 0x39, 0x09);
	cit_Packet_Format1(gspca_dev, 0x3b, 0x00);
	cit_Packet_Format1(gspca_dev, 0x28, 0x22);
	cit_Packet_Format1(gspca_dev, 0x27, 0x00);
	cit_Packet_Format1(gspca_dev, 0x2b, 0x1f);
	cit_Packet_Format1(gspca_dev, 0x39, 0x08);

	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x2c, 0x00);

	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x30, 0x14);

	cit_PacketFormat2(gspca_dev, 0x39, 0x02);
	cit_PacketFormat2(gspca_dev, 0x01, 0xe1);
	cit_PacketFormat2(gspca_dev, 0x02, 0xcd);
	cit_PacketFormat2(gspca_dev, 0x03, 0xcd);
	cit_PacketFormat2(gspca_dev, 0x04, 0xfa);
	cit_PacketFormat2(gspca_dev, 0x3f, 0xff);
	cit_PacketFormat2(gspca_dev, 0x39, 0x00);

	cit_PacketFormat2(gspca_dev, 0x39, 0x02);
	cit_PacketFormat2(gspca_dev, 0x0a, 0x37);
	cit_PacketFormat2(gspca_dev, 0x0b, 0xb8);
	cit_PacketFormat2(gspca_dev, 0x0c, 0xf3);
	cit_PacketFormat2(gspca_dev, 0x0d, 0xe3);
	cit_PacketFormat2(gspca_dev, 0x0e, 0x0d);
	cit_PacketFormat2(gspca_dev, 0x0f, 0xf2);
	cit_PacketFormat2(gspca_dev, 0x10, 0xd5);
	cit_PacketFormat2(gspca_dev, 0x11, 0xba);
	cit_PacketFormat2(gspca_dev, 0x12, 0x53);
	cit_PacketFormat2(gspca_dev, 0x3f, 0xff);
	cit_PacketFormat2(gspca_dev, 0x39, 0x00);

	cit_PacketFormat2(gspca_dev, 0x39, 0x02);
	cit_PacketFormat2(gspca_dev, 0x16, 0x00);
	cit_PacketFormat2(gspca_dev, 0x17, 0x28);
	cit_PacketFormat2(gspca_dev, 0x18, 0x7d);
	cit_PacketFormat2(gspca_dev, 0x19, 0xbe);
	cit_PacketFormat2(gspca_dev, 0x3f, 0xff);
	cit_PacketFormat2(gspca_dev, 0x39, 0x00);

	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x00, 0x18);
	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x13, 0x18);
	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x14, 0x06);

	/* TESTME These are handled through controls
	   KEEP until someone can test leaving this out is ok */
	if (0) {
		/* This is default brightness */
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x31, 0x37);
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x32, 0x46);
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x33, 0x55);
	}

	cit_Packet_Format1(gspca_dev, 0x2e, 0x04);
	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x2d, 0x04);
	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x29, 0x80);
	cit_Packet_Format1(gspca_dev, 0x2c, 0x01);
	cit_Packet_Format1(gspca_dev, 0x30, 0x17);
	cit_Packet_Format1(gspca_dev, 0x39, 0x08);
	for (i = 0; i < cit_model1_ntries; i++)
		cit_Packet_Format1(gspca_dev, 0x34, 0x00);

	cit_write_reg(gspca_dev, 0x00, 0x0101);
	cit_write_reg(gspca_dev, 0x00, 0x010a);

	switch (gspca_dev->pixfmt.width) {
	case 128: /* 128x96 */
		cit_write_reg(gspca_dev, 0x80, 0x0103);
		cit_write_reg(gspca_dev, 0x60, 0x0105);
		cit_write_reg(gspca_dev, 0x0c, 0x010b);
		cit_write_reg(gspca_dev, 0x04, 0x011b);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x0b, 0x011d);
		cit_write_reg(gspca_dev, 0x00, 0x011e);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x00, 0x0129);
		break;
	case 176: /* 176x144 */
		cit_write_reg(gspca_dev, 0xb0, 0x0103);
		cit_write_reg(gspca_dev, 0x8f, 0x0105);
		cit_write_reg(gspca_dev, 0x06, 0x010b);
		cit_write_reg(gspca_dev, 0x04, 0x011b);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x0d, 0x011d);
		cit_write_reg(gspca_dev, 0x00, 0x011e);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x03, 0x0129);
		break;
	case 352: /* 352x288 */
		cit_write_reg(gspca_dev, 0xb0, 0x0103);
		cit_write_reg(gspca_dev, 0x90, 0x0105);
		cit_write_reg(gspca_dev, 0x02, 0x010b);
		cit_write_reg(gspca_dev, 0x04, 0x011b);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x05, 0x011d);
		cit_write_reg(gspca_dev, 0x00, 0x011e);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x00, 0x0129);
		break;
	}

	cit_write_reg(gspca_dev, 0xff, 0x012b);

	/* TESTME These are handled through controls
	   KEEP until someone can test leaving this out is ok */
	if (0) {
		/* This is another brightness - don't know why */
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x31, 0xc3);
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x32, 0xd2);
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x33, 0xe1);

		/* Default contrast */
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x14, 0x0a);

		/* Default sharpness */
		for (i = 0; i < cit_model1_ntries2; i++)
			cit_PacketFormat2(gspca_dev, 0x13, 0x1a);

		/* Default lighting conditions */
		cit_Packet_Format1(gspca_dev, 0x0027,
				   v4l2_ctrl_g_ctrl(sd->lighting));
	}

	/* Assorted init */
	switch (gspca_dev->pixfmt.width) {
	case 128: /* 128x96 */
		cit_Packet_Format1(gspca_dev, 0x2b, 0x1e);
		cit_write_reg(gspca_dev, 0xc9, 0x0119);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x80, 0x0109);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x36, 0x0102);
		cit_write_reg(gspca_dev, 0x1a, 0x0104);
		cit_write_reg(gspca_dev, 0x04, 0x011a);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x2b, 0x011c);
		cit_write_reg(gspca_dev, 0x23, 0x012a);	/* Same everywhere */
		break;
	case 176: /* 176x144 */
		cit_Packet_Format1(gspca_dev, 0x2b, 0x1e);
		cit_write_reg(gspca_dev, 0xc9, 0x0119);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x80, 0x0109);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x04, 0x0102);
		cit_write_reg(gspca_dev, 0x02, 0x0104);
		cit_write_reg(gspca_dev, 0x04, 0x011a);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x2b, 0x011c);
		cit_write_reg(gspca_dev, 0x23, 0x012a);	/* Same everywhere */
		break;
	case 352: /* 352x288 */
		cit_Packet_Format1(gspca_dev, 0x2b, 0x1f);
		cit_write_reg(gspca_dev, 0xc9, 0x0119);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x80, 0x0109);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x08, 0x0102);
		cit_write_reg(gspca_dev, 0x01, 0x0104);
		cit_write_reg(gspca_dev, 0x04, 0x011a);	/* Same everywhere */
		cit_write_reg(gspca_dev, 0x2f, 0x011c);
		cit_write_reg(gspca_dev, 0x23, 0x012a);	/* Same everywhere */
		break;
	}

	cit_write_reg(gspca_dev, 0x01, 0x0100);	/* LED On  */
	cit_write_reg(gspca_dev, clock_div, 0x0111);

	return 0;
}