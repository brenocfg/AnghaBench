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
struct mlx5e_priv {struct mlx5e_ipsec* ipsec; } ;
struct mlx5e_ipsec {int /*<<< orphan*/  halloc; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drain_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_ipsec*) ; 

void mlx5e_ipsec_cleanup(struct mlx5e_priv *priv)
{
	struct mlx5e_ipsec *ipsec = priv->ipsec;

	if (!ipsec)
		return;

	drain_workqueue(ipsec->wq);
	destroy_workqueue(ipsec->wq);

	ida_destroy(&ipsec->halloc);
	kfree(ipsec);
	priv->ipsec = NULL;
}