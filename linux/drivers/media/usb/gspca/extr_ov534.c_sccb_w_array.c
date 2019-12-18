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
 int /*<<< orphan*/  sccb_reg_read (struct gspca_dev*,int const) ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int const,int const) ; 

__attribute__((used)) static void sccb_w_array(struct gspca_dev *gspca_dev,
			const u8 (*data)[2], int len)
{
	while (--len >= 0) {
		if ((*data)[0] != 0xff) {
			sccb_reg_write(gspca_dev, (*data)[0], (*data)[1]);
		} else {
			sccb_reg_read(gspca_dev, (*data)[1]);
			sccb_reg_write(gspca_dev, 0xff, 0x00);
		}
		data++;
	}
}