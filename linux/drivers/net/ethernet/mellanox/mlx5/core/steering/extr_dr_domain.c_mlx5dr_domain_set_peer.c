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
struct mlx5dr_domain {int /*<<< orphan*/  mutex; int /*<<< orphan*/  refcount; struct mlx5dr_domain* peer_dmn; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

void mlx5dr_domain_set_peer(struct mlx5dr_domain *dmn,
			    struct mlx5dr_domain *peer_dmn)
{
	mutex_lock(&dmn->mutex);

	if (dmn->peer_dmn)
		refcount_dec(&dmn->peer_dmn->refcount);

	dmn->peer_dmn = peer_dmn;

	if (dmn->peer_dmn)
		refcount_inc(&dmn->peer_dmn->refcount);

	mutex_unlock(&dmn->mutex);
}