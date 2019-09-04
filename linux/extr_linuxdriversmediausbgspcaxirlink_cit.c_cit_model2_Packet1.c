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
 int /*<<< orphan*/  cit_model2_Packet2 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void cit_model2_Packet1(struct gspca_dev *gspca_dev, u16 v1, u16 v2)
{
	cit_write_reg(gspca_dev, 0x00aa, 0x012d);
	cit_write_reg(gspca_dev, 0x00ff, 0x012e);
	cit_write_reg(gspca_dev, v1,     0x012f);
	cit_write_reg(gspca_dev, 0x00ff, 0x0130);
	cit_write_reg(gspca_dev, 0xc719, 0x0124);
	cit_write_reg(gspca_dev, v2,     0x0127);

	cit_model2_Packet2(gspca_dev);
}