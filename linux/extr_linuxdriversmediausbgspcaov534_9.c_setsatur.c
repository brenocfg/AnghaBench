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
typedef  size_t s32 ;

/* Variables and functions */
 int sccb_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setsatur(struct gspca_dev *gspca_dev, s32 val)
{
	u8 val1, val2, val3;
	static const u8 matrix[5][2] = {
		{0x14, 0x38},
		{0x1e, 0x54},
		{0x28, 0x70},
		{0x32, 0x8c},
		{0x48, 0x90}
	};

	val1 = matrix[val][0];
	val2 = matrix[val][1];
	val3 = val1 + val2;
	sccb_write(gspca_dev, 0x4f, val3);	/* matrix coeff */
	sccb_write(gspca_dev, 0x50, val3);
	sccb_write(gspca_dev, 0x51, 0x00);
	sccb_write(gspca_dev, 0x52, val1);
	sccb_write(gspca_dev, 0x53, val2);
	sccb_write(gspca_dev, 0x54, val3);
	sccb_write(gspca_dev, 0x58, 0x1a);	/* mtxs - coeff signs */

	val1 = sccb_read(gspca_dev, 0x41);	/* com16 */
	sccb_write(gspca_dev, 0xff, 0x00);
	sccb_write(gspca_dev, 0x41, val1);
}