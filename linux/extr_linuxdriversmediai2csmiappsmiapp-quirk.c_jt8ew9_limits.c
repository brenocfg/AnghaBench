#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int revision_number_major; } ;
struct smiapp_sensor {int frame_skip; TYPE_1__ minfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMIAPP_LIMIT_ANALOGUE_GAIN_CODE_MAX ; 
 int /*<<< orphan*/  SMIAPP_LIMIT_ANALOGUE_GAIN_CODE_MIN ; 
 int /*<<< orphan*/  smiapp_replace_limit (struct smiapp_sensor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jt8ew9_limits(struct smiapp_sensor *sensor)
{
	if (sensor->minfo.revision_number_major < 0x03)
		sensor->frame_skip = 1;

	/* Below 24 gain doesn't have effect at all, */
	/* but ~59 is needed for full dynamic range */
	smiapp_replace_limit(sensor, SMIAPP_LIMIT_ANALOGUE_GAIN_CODE_MIN, 59);
	smiapp_replace_limit(
		sensor, SMIAPP_LIMIT_ANALOGUE_GAIN_CODE_MAX, 6000);

	return 0;
}