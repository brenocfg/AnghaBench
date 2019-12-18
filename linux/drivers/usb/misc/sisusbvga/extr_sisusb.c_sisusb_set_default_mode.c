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
struct sisusb_usb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GETIREG (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  GETREG (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SETIREG (int /*<<< orphan*/ ,int,char const) ; 
 int /*<<< orphan*/  SETIREGAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SETIREGANDOR (int /*<<< orphan*/ ,int,int,char const) ; 
 int /*<<< orphan*/  SETIREGOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SETREG (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  SISAR ; 
 int /*<<< orphan*/  SISCR ; 
 int /*<<< orphan*/  SISGR ; 
 int /*<<< orphan*/  SISINPSTAT ; 
 int /*<<< orphan*/  SISMISCW ; 
 int /*<<< orphan*/  SISSR ; 

__attribute__((used)) static void sisusb_set_default_mode(struct sisusb_usb_data *sisusb,
		int touchengines)
{
	int i, j, modex, bpp, du;
	u8 sr31, cr63, tmp8;
	static const char attrdata[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x01, 0x00, 0x00, 0x00
	};
	static const char crtcrdata[] = {
		0x5f, 0x4f, 0x50, 0x82, 0x54, 0x80, 0x0b, 0x3e,
		0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xea, 0x8c, 0xdf, 0x28, 0x40, 0xe7, 0x04, 0xa3,
		0xff
	};
	static const char grcdata[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0f,
		0xff
	};
	static const char crtcdata[] = {
		0x5f, 0x4f, 0x4f, 0x83, 0x55, 0x81, 0x0b, 0x3e,
		0xe9, 0x8b, 0xdf, 0xe8, 0x0c, 0x00, 0x00, 0x05,
		0x00
	};

	modex = 640; bpp = 2;

	GETIREG(SISSR, 0x31, &sr31);
	GETIREG(SISCR, 0x63, &cr63);
	SETIREGOR(SISSR, 0x01, 0x20);
	SETIREG(SISCR, 0x63, cr63 & 0xbf);
	SETIREGOR(SISCR, 0x17, 0x80);
	SETIREGOR(SISSR, 0x1f, 0x04);
	SETIREGAND(SISSR, 0x07, 0xfb);
	SETIREG(SISSR, 0x00, 0x03);	/* seq */
	SETIREG(SISSR, 0x01, 0x21);
	SETIREG(SISSR, 0x02, 0x0f);
	SETIREG(SISSR, 0x03, 0x00);
	SETIREG(SISSR, 0x04, 0x0e);
	SETREG(SISMISCW, 0x23);		/* misc */
	for (i = 0; i <= 0x18; i++) {	/* crtc */
		SETIREG(SISCR, i, crtcrdata[i]);
	}
	for (i = 0; i <= 0x13; i++) {	/* att */
		GETREG(SISINPSTAT, &tmp8);
		SETREG(SISAR, i);
		SETREG(SISAR, attrdata[i]);
	}
	GETREG(SISINPSTAT, &tmp8);
	SETREG(SISAR, 0x14);
	SETREG(SISAR, 0x00);
	GETREG(SISINPSTAT, &tmp8);
	SETREG(SISAR, 0x20);
	GETREG(SISINPSTAT, &tmp8);
	for (i = 0; i <= 0x08; i++) {	/* grc */
		SETIREG(SISGR, i, grcdata[i]);
	}
	SETIREGAND(SISGR, 0x05, 0xbf);
	for (i = 0x0A; i <= 0x0E; i++) {	/* clr ext */
		SETIREG(SISSR, i, 0x00);
	}
	SETIREGAND(SISSR, 0x37, 0xfe);
	SETREG(SISMISCW, 0xef);		/* sync */
	SETIREG(SISCR, 0x11, 0x00);	/* crtc */
	for (j = 0x00, i = 0; i <= 7; i++, j++)
		SETIREG(SISCR, j, crtcdata[i]);

	for (j = 0x10; i <= 10; i++, j++)
		SETIREG(SISCR, j, crtcdata[i]);

	for (j = 0x15; i <= 12; i++, j++)
		SETIREG(SISCR, j, crtcdata[i]);

	for (j = 0x0A; i <= 15; i++, j++)
		SETIREG(SISSR, j, crtcdata[i]);

	SETIREG(SISSR, 0x0E, (crtcdata[16] & 0xE0));
	SETIREGANDOR(SISCR, 0x09, 0x5f, ((crtcdata[16] & 0x01) << 5));
	SETIREG(SISCR, 0x14, 0x4f);
	du = (modex / 16) * (bpp * 2);	/* offset/pitch */
	SETIREGANDOR(SISSR, 0x0e, 0xf0, ((du >> 8) & 0x0f));
	SETIREG(SISCR, 0x13, (du & 0xff));
	du <<= 5;
	tmp8 = du >> 8;
	SETIREG(SISSR, 0x10, tmp8);
	SETIREG(SISSR, 0x31, 0x00);	/* VCLK */
	SETIREG(SISSR, 0x2b, 0x1b);
	SETIREG(SISSR, 0x2c, 0xe1);
	SETIREG(SISSR, 0x2d, 0x01);
	SETIREGAND(SISSR, 0x3d, 0xfe);	/* FIFO */
	SETIREG(SISSR, 0x08, 0xae);
	SETIREGAND(SISSR, 0x09, 0xf0);
	SETIREG(SISSR, 0x08, 0x34);
	SETIREGOR(SISSR, 0x3d, 0x01);
	SETIREGAND(SISSR, 0x1f, 0x3f);	/* mode regs */
	SETIREGANDOR(SISSR, 0x06, 0xc0, 0x0a);
	SETIREG(SISCR, 0x19, 0x00);
	SETIREGAND(SISCR, 0x1a, 0xfc);
	SETIREGAND(SISSR, 0x0f, 0xb7);
	SETIREGAND(SISSR, 0x31, 0xfb);
	SETIREGANDOR(SISSR, 0x21, 0x1f, 0xa0);
	SETIREGAND(SISSR, 0x32, 0xf3);
	SETIREGANDOR(SISSR, 0x07, 0xf8, 0x03);
	SETIREG(SISCR, 0x52, 0x6c);

	SETIREG(SISCR, 0x0d, 0x00);	/* adjust frame */
	SETIREG(SISCR, 0x0c, 0x00);
	SETIREG(SISSR, 0x0d, 0x00);
	SETIREGAND(SISSR, 0x37, 0xfe);

	SETIREG(SISCR, 0x32, 0x20);
	SETIREGAND(SISSR, 0x01, 0xdf);	/* enable display */
	SETIREG(SISCR, 0x63, (cr63 & 0xbf));
	SETIREG(SISSR, 0x31, (sr31 & 0xfb));

	if (touchengines) {
		SETIREG(SISSR, 0x20, 0xa1);	/* enable engines */
		SETIREGOR(SISSR, 0x1e, 0x5a);

		SETIREG(SISSR, 0x26, 0x01);	/* disable cmdqueue */
		SETIREG(SISSR, 0x27, 0x1f);
		SETIREG(SISSR, 0x26, 0x00);
	}

	SETIREG(SISCR, 0x34, 0x44);	/* we just set std mode #44 */
}