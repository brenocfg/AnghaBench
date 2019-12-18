#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int vif_num; } ;
struct ar9170 {TYPE_4__* if_combs; TYPE_3__* hw; TYPE_4__* if_comb_limits; TYPE_1__ fw; } ;
struct TYPE_8__ {int max; int num_different_channels; int max_interfaces; void* n_limits; struct TYPE_8__* limits; int /*<<< orphan*/  types; } ;
struct TYPE_7__ {TYPE_2__* wiphy; } ;
struct TYPE_6__ {void* n_iface_combinations; TYPE_4__* iface_combinations; } ;

/* Variables and functions */
 void* ARRAY_SIZE (TYPE_4__*) ; 

__attribute__((used)) static void carl9170_fw_set_if_combinations(struct ar9170 *ar,
					    u16 if_comb_types)
{
	if (ar->fw.vif_num < 2)
		return;

	ar->if_comb_limits[0].max = ar->fw.vif_num;
	ar->if_comb_limits[0].types = if_comb_types;

	ar->if_combs[0].num_different_channels = 1;
	ar->if_combs[0].max_interfaces = ar->fw.vif_num;
	ar->if_combs[0].limits = ar->if_comb_limits;
	ar->if_combs[0].n_limits = ARRAY_SIZE(ar->if_comb_limits);

	ar->hw->wiphy->iface_combinations = ar->if_combs;
	ar->hw->wiphy->n_iface_combinations = ARRAY_SIZE(ar->if_combs);
}