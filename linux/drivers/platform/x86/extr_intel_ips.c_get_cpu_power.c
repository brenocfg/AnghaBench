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
struct ips_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THM_CEC ; 
 int thm_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_cpu_power(struct ips_driver *ips, u32 *last, int period)
{
	u32 val;
	u32 ret;

	/*
	 * CEC is in joules/65535.  Take difference over time to
	 * get watts.
	 */
	val = thm_readl(THM_CEC);

	/* period is in ms and we want mW */
	ret = (((val - *last) * 1000) / period);
	ret = (ret * 1000) / 65535;
	*last = val;

	return 0;
}