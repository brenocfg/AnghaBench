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
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm_sensor_power_on(struct stm_thermal_sensor *sensor)
{
	int ret;
	u32 value;

	/* Enable sensor */
	value = readl_relaxed(sensor->base + DTS_CFGR1_OFFSET);
	value |= TS1_EN;
	writel_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	/*
	 * The DTS block can be enabled by setting TSx_EN bit in
	 * DTS_CFGRx register. It requires a startup time of
	 * 40μs. Use 5 ms as arbitrary timeout.
	 */
	ret = readl_poll_timeout(sensor->base + DTS_SR_OFFSET,
				 value, (value & TS_RDY),
				 STARTUP_TIME, POLL_TIMEOUT);
	if (ret)
		return ret;

	/* Start continuous measuring */
	value = readl_relaxed(sensor->base +
			      DTS_CFGR1_OFFSET);
	value |= TS1_START;
	writel_relaxed(value, sensor->base +
		       DTS_CFGR1_OFFSET);

	return 0;
}