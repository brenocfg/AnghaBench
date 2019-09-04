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
struct sd {int norme; int channel; } ;
struct gspca_dev {int /*<<< orphan*/  dev; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  reg_w (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  spca506_Initi2c (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca506_WriteI2c (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void spca506_SetNormeInput(struct gspca_dev *gspca_dev,
				 __u16 norme,
				 __u16 channel)
{
	struct sd *sd = (struct sd *) gspca_dev;
/* fixme: check if channel == 0..3 and 6..9 (8 values) */
	__u8 setbit0 = 0x00;
	__u8 setbit1 = 0x00;
	__u8 videomask = 0x00;

	gspca_dbg(gspca_dev, D_STREAM, "** Open Set Norme **\n");
	spca506_Initi2c(gspca_dev);
	/* NTSC bit0 -> 1(525 l) PAL SECAM bit0 -> 0 (625 l) */
	/* Composite channel bit1 -> 1 S-video bit 1 -> 0 */
	/* and exclude SAA7113 reserved channel set default 0 otherwise */
	if (norme & V4L2_STD_NTSC)
		setbit0 = 0x01;
	if (channel == 4 || channel == 5 || channel > 9)
		channel = 0;
	if (channel < 4)
		setbit1 = 0x02;
	videomask = (0x48 | setbit0 | setbit1);
	reg_w(gspca_dev->dev, 0x08, videomask, 0x0000);
	spca506_WriteI2c(gspca_dev, (0xc0 | (channel & 0x0F)), 0x02);

	if (norme & V4L2_STD_NTSC)
		spca506_WriteI2c(gspca_dev, 0x33, 0x0e);
					/* Chrominance Control NTSC N */
	else if (norme & V4L2_STD_SECAM)
		spca506_WriteI2c(gspca_dev, 0x53, 0x0e);
					/* Chrominance Control SECAM */
	else
		spca506_WriteI2c(gspca_dev, 0x03, 0x0e);
					/* Chrominance Control PAL BGHIV */

	sd->norme = norme;
	sd->channel = channel;
	gspca_dbg(gspca_dev, D_STREAM, "Set Video Byte to 0x%2x\n", videomask);
	gspca_dbg(gspca_dev, D_STREAM, "Set Norme: %08x Channel %d",
		  norme, channel);
}