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
struct hisi_pmu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void hisi_ddrc_pmu_write_evtype(struct hisi_pmu *hha_pmu, int idx,
				       u32 type)
{
}