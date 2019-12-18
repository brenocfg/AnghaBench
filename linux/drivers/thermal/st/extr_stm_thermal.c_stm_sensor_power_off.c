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
typedef  int u32 ;
struct stm_thermal_sensor {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DTS_CFGR1_OFFSET ; 
 scalar_t__ DTS_SR_OFFSET ; 
 int /*<<< orphan*/  POLL_TIMEOUT ; 
 int /*<<< orphan*/  STARTUP_TIME ; 
 int TS1_EN ; 
 int TS1_START ; 
 int TS_RDY ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm_sensor_power_off(struct stm_thermal_sensor *sensor)
{
	u32 value;

	/* Stop measuring */
	value = readl_relaxed(sensor->base + DTS_CFGR1_OFFSET);
	value &= ~TS1_START;
	writel_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	/* Ensure stop is taken into account */
	usleep_range(STARTUP_TIME, POLL_TIMEOUT);

	/* Disable sensor */
	value = readl_relaxed(sensor->base + DTS_CFGR1_OFFSET);
	value &= ~TS1_EN;
	writel_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	/* Ensure disable is taken into account */
	return readl_poll_timeout(sensor->base + DTS_SR_OFFSET, value,
				  !(value & TS_RDY),
				  STARTUP_TIME, POLL_TIMEOUT);
}