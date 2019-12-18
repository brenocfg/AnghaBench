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
typedef  int /*<<< orphan*/  u64 ;
struct rapl_domain {int dummy; } ;
struct powercap_zone {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENERGY_COUNTER ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 struct rapl_domain* power_zone_to_rapl_domain (struct powercap_zone*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  rapl_read_data_raw (struct rapl_domain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_energy_counter(struct powercap_zone *power_zone,
			      u64 *energy_raw)
{
	struct rapl_domain *rd;
	u64 energy_now;

	/* prevent CPU hotplug, make sure the RAPL domain does not go
	 * away while reading the counter.
	 */
	get_online_cpus();
	rd = power_zone_to_rapl_domain(power_zone);

	if (!rapl_read_data_raw(rd, ENERGY_COUNTER, true, &energy_now)) {
		*energy_raw = energy_now;
		put_online_cpus();

		return 0;
	}
	put_online_cpus();

	return -EIO;
}