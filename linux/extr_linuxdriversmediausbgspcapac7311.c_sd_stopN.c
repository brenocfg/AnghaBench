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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	reg_w(gspca_dev, 0xff, 0x04);
	reg_w(gspca_dev, 0x27, 0x80);
	reg_w(gspca_dev, 0x28, 0xca);
	reg_w(gspca_dev, 0x29, 0x53);
	reg_w(gspca_dev, 0x2a, 0x0e);
	reg_w(gspca_dev, 0xff, 0x01);
	reg_w(gspca_dev, 0x3e, 0x20);
	reg_w(gspca_dev, 0x78, 0x44); /* Bit_0=start stream, Bit_6=LED */
	reg_w(gspca_dev, 0x78, 0x44); /* Bit_0=start stream, Bit_6=LED */
	reg_w(gspca_dev, 0x78, 0x44); /* Bit_0=start stream, Bit_6=LED */
}