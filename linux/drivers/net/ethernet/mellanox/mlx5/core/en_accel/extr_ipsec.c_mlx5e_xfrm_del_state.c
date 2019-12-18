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
struct TYPE_2__ {int flags; } ;
struct xfrm_state {TYPE_1__ xso; } ;
struct mlx5e_ipsec_sa_entry {int dummy; } ;

/* Variables and functions */
 int XFRM_OFFLOAD_INBOUND ; 
 int /*<<< orphan*/  mlx5e_ipsec_sadb_rx_del (struct mlx5e_ipsec_sa_entry*) ; 
 struct mlx5e_ipsec_sa_entry* to_ipsec_sa_entry (struct xfrm_state*) ; 

__attribute__((used)) static void mlx5e_xfrm_del_state(struct xfrm_state *x)
{
	struct mlx5e_ipsec_sa_entry *sa_entry = to_ipsec_sa_entry(x);

	if (!sa_entry)
		return;

	if (x->xso.flags & XFRM_OFFLOAD_INBOUND)
		mlx5e_ipsec_sadb_rx_del(sa_entry);
}