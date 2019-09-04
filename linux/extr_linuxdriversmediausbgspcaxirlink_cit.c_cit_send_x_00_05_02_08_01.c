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
typedef  int u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void cit_send_x_00_05_02_08_01(struct gspca_dev *gspca_dev, u16 x)
{
	cit_write_reg(gspca_dev, x,      0x0127);
	cit_write_reg(gspca_dev, 0x0000, 0x0124);
	cit_write_reg(gspca_dev, 0x0005, 0x0124);
	cit_write_reg(gspca_dev, 0x0002, 0x0124);
	cit_write_reg(gspca_dev, 0x0008, 0x0124);
	cit_write_reg(gspca_dev, 0x0001, 0x0124);
}