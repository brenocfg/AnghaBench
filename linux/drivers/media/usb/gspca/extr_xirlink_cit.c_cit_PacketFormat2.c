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
typedef  int /*<<< orphan*/  u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cit_send_x_00_05 (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cit_send_x_00_05_02 (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cit_send_x_01_00_05 (struct gspca_dev*,int) ; 

__attribute__((used)) static void cit_PacketFormat2(struct gspca_dev *gspca_dev, u16 fkey, u16 val)
{
	cit_send_x_01_00_05(gspca_dev, 0x0088);
	cit_send_x_00_05(gspca_dev, fkey);
	cit_send_x_00_05_02(gspca_dev, val);
}