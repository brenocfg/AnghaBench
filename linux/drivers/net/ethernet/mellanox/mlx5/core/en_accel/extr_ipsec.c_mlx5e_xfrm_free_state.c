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
struct TYPE_4__ {int flags; } ;
struct xfrm_state {TYPE_2__ xso; } ;
struct mlx5e_ipsec_sa_entry {int /*<<< orphan*/  xfrm; scalar_t__ hw_context; TYPE_1__* ipsec; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int XFRM_OFFLOAD_INBOUND ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_ipsec_sa_entry*) ; 
 int /*<<< orphan*/  mlx5_accel_esp_destroy_xfrm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_accel_esp_free_hw_context (scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_ipsec_sadb_rx_free (struct mlx5e_ipsec_sa_entry*) ; 
 struct mlx5e_ipsec_sa_entry* to_ipsec_sa_entry (struct xfrm_state*) ; 

__attribute__((used)) static void mlx5e_xfrm_free_state(struct xfrm_state *x)
{
	struct mlx5e_ipsec_sa_entry *sa_entry = to_ipsec_sa_entry(x);

	if (!sa_entry)
		return;

	if (sa_entry->hw_context) {
		flush_workqueue(sa_entry->ipsec->wq);
		mlx5_accel_esp_free_hw_context(sa_entry->hw_context);
		mlx5_accel_esp_destroy_xfrm(sa_entry->xfrm);
	}

	if (x->xso.flags & XFRM_OFFLOAD_INBOUND)
		mlx5e_ipsec_sadb_rx_free(sa_entry);

	kfree(sa_entry);
}