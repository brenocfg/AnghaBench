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
struct mlx5e_ipsec_sa_entry {int /*<<< orphan*/  handle; struct mlx5e_ipsec* ipsec; } ;
struct mlx5e_ipsec {int /*<<< orphan*/  halloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_ipsec_sadb_rx_free(struct mlx5e_ipsec_sa_entry *sa_entry)
{
	struct mlx5e_ipsec *ipsec = sa_entry->ipsec;

	/* xfrm already doing sync rcu between del and free callbacks */

	ida_simple_remove(&ipsec->halloc, sa_entry->handle);
}