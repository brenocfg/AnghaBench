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
typedef  int u8 ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int CAMQUALITY_MAX ; 
 int QUALITY_MAX ; 
 int QUALITY_MIN ; 
 int /*<<< orphan*/  jlj_write2 (struct gspca_dev*,int*) ; 

__attribute__((used)) static void setcamquality(struct gspca_dev *gspca_dev, s32 val)
{
	u8 quality_commands[][2] = {
		{0x71, 0x1E},
		{0x70, 0x06}
	};
	u8 camquality;

	/* adapt camera quality from jpeg quality */
	camquality = ((QUALITY_MAX - val) * CAMQUALITY_MAX)
		/ (QUALITY_MAX - QUALITY_MIN);
	quality_commands[0][1] += camquality;

	jlj_write2(gspca_dev, quality_commands[0]);
	jlj_write2(gspca_dev, quality_commands[1]);
}