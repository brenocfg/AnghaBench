#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t noa_len; void* noa_data; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;
struct ath10k_vif {TYPE_2__ u; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_p2p_noa_ie_assign(struct ath10k_vif *arvif, void *ie,
				     size_t len)
{
	struct ath10k *ar = arvif->ar;

	lockdep_assert_held(&ar->data_lock);

	kfree(arvif->u.ap.noa_data);

	arvif->u.ap.noa_data = ie;
	arvif->u.ap.noa_len = len;
}