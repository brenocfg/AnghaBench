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
typedef  int __u16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  msleep (int) ; 
 int reg_r_12 (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static int reg_r_wait(struct gspca_dev *gspca_dev,
			__u16 reg, __u16 index, __u16 value)
{
	int ret, cnt = 20;

	while (--cnt > 0) {
		ret = reg_r_12(gspca_dev, reg, index, 1);
		if (ret == value)
			return 0;
		msleep(50);
	}
	return -EIO;
}