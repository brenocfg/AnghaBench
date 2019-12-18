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
 int /*<<< orphan*/  R3B_Test3 ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	reg_w1(gspca_dev, R3B_Test3, 0x0b);	/* Test0Sel = 11 = GPIO */
}