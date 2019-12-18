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
struct smiapp_sensor {int dummy; } ;

/* Variables and functions */
 int smiapp_write_8 (struct smiapp_sensor*,int,int) ; 

__attribute__((used)) static int jt8ev1_pre_streamon(struct smiapp_sensor *sensor)
{
	return smiapp_write_8(sensor, 0x3328, 0x00);
}