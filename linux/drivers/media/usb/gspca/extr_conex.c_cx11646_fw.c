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

/* Variables and functions */
 scalar_t__** cx11646_fw1 ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void cx11646_fw(struct gspca_dev*gspca_dev)
{
	int i = 0;

	reg_w_val(gspca_dev, 0x006a, 0x02);
	while (cx11646_fw1[i][1]) {
		reg_w(gspca_dev, 0x006b, cx11646_fw1[i], 3);
		i++;
	}
	reg_w_val(gspca_dev, 0x006a, 0x00);
}