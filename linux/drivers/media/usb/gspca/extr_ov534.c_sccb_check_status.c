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
 int /*<<< orphan*/  OV534_REG_STATUS ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,int,int) ; 
 int ov534_reg_read (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sccb_check_status(struct gspca_dev *gspca_dev)
{
	u8 data;
	int i;

	for (i = 0; i < 5; i++) {
		usleep_range(10000, 20000);
		data = ov534_reg_read(gspca_dev, OV534_REG_STATUS);

		switch (data) {
		case 0x00:
			return 1;
		case 0x04:
			return 0;
		case 0x03:
			break;
		default:
			gspca_err(gspca_dev, "sccb status 0x%02x, attempt %d/5\n",
				  data, i + 1);
		}
	}
	return 0;
}