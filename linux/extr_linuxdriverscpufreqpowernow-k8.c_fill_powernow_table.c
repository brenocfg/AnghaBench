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
typedef  int /*<<< orphan*/  u8 ;
struct pst_s {scalar_t__ fid; int vid; } ;
struct powernow_k8_data {unsigned int batps; unsigned int numps; scalar_t__ currfid; int currvid; scalar_t__ cpu; struct cpufreq_frequency_table* powernow_table; } ;
struct cpufreq_frequency_table {int driver_data; int frequency; } ;

/* Variables and functions */
 int CPUFREQ_TABLE_END ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ check_pst_table (struct powernow_k8_data*,struct pst_s*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_first (int /*<<< orphan*/ ) ; 
 int find_khz_freq_from_fid (int) ; 
 int /*<<< orphan*/  kfree (struct cpufreq_frequency_table*) ; 
 struct cpufreq_frequency_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 int /*<<< orphan*/  print_basics (struct powernow_k8_data*) ; 
 scalar_t__ query_current_values_with_pending_wait (struct powernow_k8_data*) ; 
 int /*<<< orphan*/  topology_core_cpumask (scalar_t__) ; 

__attribute__((used)) static int fill_powernow_table(struct powernow_k8_data *data,
		struct pst_s *pst, u8 maxvid)
{
	struct cpufreq_frequency_table *powernow_table;
	unsigned int j;

	if (data->batps) {
		/* use ACPI support to get full speed on mains power */
		pr_warn("Only %d pstates usable (use ACPI driver for full range\n",
			data->batps);
		data->numps = data->batps;
	}

	for (j = 1; j < data->numps; j++) {
		if (pst[j-1].fid >= pst[j].fid) {
			pr_err("PST out of sequence\n");
			return -EINVAL;
		}
	}

	if (data->numps < 2) {
		pr_err("no p states to transition\n");
		return -ENODEV;
	}

	if (check_pst_table(data, pst, maxvid))
		return -EINVAL;

	powernow_table = kzalloc((sizeof(*powernow_table)
		* (data->numps + 1)), GFP_KERNEL);
	if (!powernow_table)
		return -ENOMEM;

	for (j = 0; j < data->numps; j++) {
		int freq;
		powernow_table[j].driver_data = pst[j].fid; /* lower 8 bits */
		powernow_table[j].driver_data |= (pst[j].vid << 8); /* upper 8 bits */
		freq = find_khz_freq_from_fid(pst[j].fid);
		powernow_table[j].frequency = freq;
	}
	powernow_table[data->numps].frequency = CPUFREQ_TABLE_END;
	powernow_table[data->numps].driver_data = 0;

	if (query_current_values_with_pending_wait(data)) {
		kfree(powernow_table);
		return -EIO;
	}

	pr_debug("cfid 0x%x, cvid 0x%x\n", data->currfid, data->currvid);
	data->powernow_table = powernow_table;
	if (cpumask_first(topology_core_cpumask(data->cpu)) == data->cpu)
		print_basics(data);

	for (j = 0; j < data->numps; j++)
		if ((pst[j].fid == data->currfid) &&
		    (pst[j].vid == data->currvid))
			return 0;

	pr_debug("currfid/vid do not match PST, ignoring\n");
	return 0;
}