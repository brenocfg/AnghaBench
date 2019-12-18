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
struct rapl_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL1_CLAMP ; 
 int /*<<< orphan*/  PL2_CLAMP ; 
 int /*<<< orphan*/  PL2_ENABLE ; 
 int find_nr_power_limit (struct rapl_domain*) ; 
 int /*<<< orphan*/  rapl_write_data_raw (struct rapl_domain*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_floor_freq_default(struct rapl_domain *rd, bool mode)
{
	int nr_powerlimit = find_nr_power_limit(rd);

	/* always enable clamp such that p-state can go below OS requested
	 * range. power capping priority over guranteed frequency.
	 */
	rapl_write_data_raw(rd, PL1_CLAMP, mode);

	/* some domains have pl2 */
	if (nr_powerlimit > 1) {
		rapl_write_data_raw(rd, PL2_ENABLE, mode);
		rapl_write_data_raw(rd, PL2_CLAMP, mode);
	}
}