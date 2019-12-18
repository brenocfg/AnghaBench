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
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV9650_COM2 ; 
 int OV9650_OUTPUT_DRIVE_2X ; 
 int OV9650_SOFT_SLEEP ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

int ov9650_stop(struct sd *sd)
{
	u8 data = OV9650_SOFT_SLEEP | OV9650_OUTPUT_DRIVE_2X;
	return m5602_write_sensor(sd, OV9650_COM2, &data, 1);
}