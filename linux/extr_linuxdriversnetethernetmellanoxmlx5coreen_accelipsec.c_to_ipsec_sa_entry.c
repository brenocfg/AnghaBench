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
struct TYPE_2__ {scalar_t__ offload_handle; } ;
struct xfrm_state {TYPE_1__ xso; } ;
struct mlx5e_ipsec_sa_entry {struct xfrm_state* x; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static struct mlx5e_ipsec_sa_entry *to_ipsec_sa_entry(struct xfrm_state *x)
{
	struct mlx5e_ipsec_sa_entry *sa;

	if (!x)
		return NULL;

	sa = (struct mlx5e_ipsec_sa_entry *)x->xso.offload_handle;
	if (!sa)
		return NULL;

	WARN_ON(sa->x != x);
	return sa;
}