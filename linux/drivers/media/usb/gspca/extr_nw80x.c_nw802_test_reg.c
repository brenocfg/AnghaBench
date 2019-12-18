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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct gspca_dev {scalar_t__* usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int nw802_test_reg(struct gspca_dev *gspca_dev,
			u16 index,
			u8 value)
{
	/* write the value */
	reg_w(gspca_dev, index, &value, 1);

	/* read it */
	reg_r(gspca_dev, index, 1);

	return gspca_dev->usb_buf[0] == value;
}