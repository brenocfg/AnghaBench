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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int const*,int) ; 

__attribute__((used)) static void poll_sensor(struct gspca_dev *gspca_dev)
{
	static const u8 poll1[] =
		{0x67, 0x05, 0x68, 0x81, 0x69, 0x80, 0x6a, 0x82,
		 0x6b, 0x68, 0x6c, 0x69, 0x72, 0xd9, 0x73, 0x34,
		 0x74, 0x32, 0x75, 0x92, 0x76, 0x00, 0x09, 0x01,
		 0x60, 0x14};
	static const u8 poll2[] =
		{0x67, 0x02, 0x68, 0x71, 0x69, 0x72, 0x72, 0xa9,
		 0x73, 0x02, 0x73, 0x02, 0x60, 0x14};
	static const u8 noise03[] =	/* (some differences / ms-drv) */
		{0xa6, 0x0a, 0xea, 0xcf, 0xbe, 0x26, 0xb1, 0x5f,
		 0xa1, 0xb1, 0xda, 0x6b, 0xdb, 0x98, 0xdf, 0x0c,
		 0xc2, 0x80, 0xc3, 0x10};

	gspca_dbg(gspca_dev, D_STREAM, "[Sensor requires polling]\n");
	reg_w_buf(gspca_dev, poll1, sizeof poll1);
	reg_w_buf(gspca_dev, poll2, sizeof poll2);
	reg_w_buf(gspca_dev, noise03, sizeof noise03);
}