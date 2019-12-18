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
typedef  int s32 ;
typedef  int __u8 ;

/* Variables and functions */
 int* reg10 ; 
 int /*<<< orphan*/  reg70 ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setcontrast(struct gspca_dev *gspca_dev, s32 val, s32 sat)
{
	__u8 regE5acx[] = { 0x88, 0x0a, 0x0c, 0x01 };	/* seem MSB */
/*	__u8 regE5bcx[] = { 0x88, 0x0b, 0x12, 0x01};	 * LSB */
	__u8 reg51c[2];

	regE5acx[2] = val;
	reg_w(gspca_dev, 0x00e5, regE5acx, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */
	reg51c[0] = 0x77;
	reg51c[1] = sat;
	reg_w(gspca_dev, 0x0051, reg51c, 2);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0070, reg70);
}