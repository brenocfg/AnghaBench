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
struct TYPE_2__ {scalar_t__ rmt_start; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 scalar_t__ NUM_MAP_ENTRIES ; 

__attribute__((used)) static inline bool hfi1_vnic_is_rsm_full(struct hfi1_devdata *dd, int spare)
{
	return (dd->vnic.rmt_start + spare) > NUM_MAP_ENTRIES;
}