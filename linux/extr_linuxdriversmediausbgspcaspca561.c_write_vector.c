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
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static void write_vector(struct gspca_dev *gspca_dev,
			const __u16 data[][2])
{
	int i;

	i = 0;
	while (data[i][1] != 0) {
		reg_w_val(gspca_dev, data[i][1], data[i][0]);
		i++;
	}
}