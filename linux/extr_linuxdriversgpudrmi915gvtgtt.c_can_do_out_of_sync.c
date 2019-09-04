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
struct TYPE_2__ {int write_cnt; int /*<<< orphan*/  type; } ;
struct intel_vgpu_ppgtt_spt {TYPE_1__ guest_page; } ;

/* Variables and functions */
 scalar_t__ enable_out_of_sync ; 
 scalar_t__ gtt_type_is_pte_pt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool can_do_out_of_sync(struct intel_vgpu_ppgtt_spt *spt)
{
	return enable_out_of_sync
		&& gtt_type_is_pte_pt(spt->guest_page.type)
		&& spt->guest_page.write_cnt >= 2;
}