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
 int /*<<< orphan*/  SMIAPP_QUIRK_FLAG_8BIT_READ_ONLY ; 
 int __smiapp_read (struct smiapp_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smiapp_needs_quirk (struct smiapp_sensor*,int /*<<< orphan*/ ) ; 

int smiapp_read_no_quirk(struct smiapp_sensor *sensor, u32 reg, u32 *val)
{
	return __smiapp_read(
		sensor, reg, val,
		smiapp_needs_quirk(sensor,
				   SMIAPP_QUIRK_FLAG_8BIT_READ_ONLY));
}