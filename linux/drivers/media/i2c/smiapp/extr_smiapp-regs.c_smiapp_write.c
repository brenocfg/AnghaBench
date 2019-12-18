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
typedef  int /*<<< orphan*/  u32 ;
struct smiapp_sensor {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  reg_access ; 
 int smiapp_call_quirk (struct smiapp_sensor*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int smiapp_write_no_quirk (struct smiapp_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smiapp_write(struct smiapp_sensor *sensor, u32 reg, u32 val)
{
	int rval;

	rval = smiapp_call_quirk(sensor, reg_access, true, &reg, &val);
	if (rval == -ENOIOCTLCMD)
		return 0;
	if (rval < 0)
		return rval;

	return smiapp_write_no_quirk(sensor, reg, val);
}