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
typedef  scalar_t__ u32 ;
struct dpu_kms {int dummy; } ;

/* Variables and functions */
 scalar_t__ DPU_POWER_EVENT_POST_ENABLE ; 
 int /*<<< orphan*/  dpu_vbif_init_memtypes (struct dpu_kms*) ; 

__attribute__((used)) static void dpu_kms_handle_power_event(u32 event_type, void *usr)
{
	struct dpu_kms *dpu_kms = usr;

	if (!dpu_kms)
		return;

	if (event_type == DPU_POWER_EVENT_POST_ENABLE)
		dpu_vbif_init_memtypes(dpu_kms);
}