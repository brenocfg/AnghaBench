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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int reg_write (struct gspca_dev*,scalar_t__ const,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static int write_vector(struct gspca_dev *gspca_dev,
			const u8 data[][3])
{
	int ret, i = 0;

	while (data[i][0] != 0) {
		ret = reg_write(gspca_dev, data[i][0], data[i][2],
								data[i][1]);
		if (ret < 0)
			return ret;
		i++;
	}
	return 0;
}