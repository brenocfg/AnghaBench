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
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int const) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 exposure)
{
	static const u8 expo[4] = {0x00, 0x25, 0x38, 0x5e};
	u8 val;

	sccb_write(gspca_dev, 0x10, expo[exposure]);	/* aec[9:2] */

	val = sccb_read(gspca_dev, 0x13);		/* com8 */
	sccb_write(gspca_dev, 0xff, 0x00);
	sccb_write(gspca_dev, 0x13, val);

	val = sccb_read(gspca_dev, 0xa1);		/* aech */
	sccb_write(gspca_dev, 0xff, 0x00);
	sccb_write(gspca_dev, 0xa1, val & 0xe0);	/* aec[15:10] = 0 */
}