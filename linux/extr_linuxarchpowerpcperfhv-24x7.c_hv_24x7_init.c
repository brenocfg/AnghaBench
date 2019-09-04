#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hv_perf_caps {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  oprofile_cpu_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  attrs; } ;
struct TYPE_9__ {int /*<<< orphan*/  attrs; } ;
struct TYPE_8__ {int /*<<< orphan*/  attrs; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  PERF_PMU_CAP_NO_INTERRUPT ; 
 int aggregate_result_elements ; 
 int create_events_from_catalog (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* cur_cpu_spec ; 
 TYPE_5__ event_desc_group ; 
 TYPE_4__ event_group ; 
 TYPE_3__ event_long_desc_group ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__ h_24x7_pmu ; 
 int /*<<< orphan*/  hv_page_cache ; 
 unsigned long hv_perf_caps_get (struct hv_perf_caps*) ; 
 int interface_version ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perf_pmu_register (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int threads_per_core ; 

__attribute__((used)) static int hv_24x7_init(void)
{
	int r;
	unsigned long hret;
	struct hv_perf_caps caps;

	if (!firmware_has_feature(FW_FEATURE_LPAR)) {
		pr_debug("not a virtualized system, not enabling\n");
		return -ENODEV;
	} else if (!cur_cpu_spec->oprofile_cpu_type)
		return -ENODEV;

	/* POWER8 only supports v1, while POWER9 only supports v2. */
	if (!strcmp(cur_cpu_spec->oprofile_cpu_type, "ppc64/power8"))
		interface_version = 1;
	else {
		interface_version = 2;

		/* SMT8 in POWER9 needs to aggregate result elements. */
		if (threads_per_core == 8)
			aggregate_result_elements = true;
	}

	hret = hv_perf_caps_get(&caps);
	if (hret) {
		pr_debug("could not obtain capabilities, not enabling, rc=%ld\n",
				hret);
		return -ENODEV;
	}

	hv_page_cache = kmem_cache_create("hv-page-4096", 4096, 4096, 0, NULL);
	if (!hv_page_cache)
		return -ENOMEM;

	/* sampling not supported */
	h_24x7_pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;

	r = create_events_from_catalog(&event_group.attrs,
				   &event_desc_group.attrs,
				   &event_long_desc_group.attrs);

	if (r)
		return r;

	r = perf_pmu_register(&h_24x7_pmu, h_24x7_pmu.name, -1);
	if (r)
		return r;

	return 0;
}