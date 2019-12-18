#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int member_1; } ;
typedef  TYPE_1__ u8 ;
struct gspca_dev {int dummy; } ;
typedef  TYPE_1__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  jlj_write2 (struct gspca_dev*,TYPE_1__*) ; 

__attribute__((used)) static void setblue(struct gspca_dev *gspca_dev, s32 val)
{
	u8 setblue_commands[][2] = {
		{0x94, 0x02},
		{0xe9, 0x00}
	};

	setblue_commands[1][1] = val;

	jlj_write2(gspca_dev, setblue_commands[0]);
	jlj_write2(gspca_dev, setblue_commands[1]);
}