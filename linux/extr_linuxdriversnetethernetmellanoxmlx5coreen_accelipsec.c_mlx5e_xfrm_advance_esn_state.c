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
struct xfrm_state {int dummy; } ;
struct mlx5e_ipsec_sa_entry {TYPE_1__* ipsec; } ;
struct mlx5e_ipsec_modify_state_work {int /*<<< orphan*/  work; struct mlx5e_ipsec_sa_entry* sa_entry; int /*<<< orphan*/  attrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _update_xfrm_state ; 
 struct mlx5e_ipsec_modify_state_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_ipsec_build_accel_xfrm_attrs (struct mlx5e_ipsec_sa_entry*,int /*<<< orphan*/ *) ; 
 int mlx5e_ipsec_update_esn_state (struct mlx5e_ipsec_sa_entry*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5e_ipsec_sa_entry* to_ipsec_sa_entry (struct xfrm_state*) ; 

__attribute__((used)) static void mlx5e_xfrm_advance_esn_state(struct xfrm_state *x)
{
	struct mlx5e_ipsec_sa_entry *sa_entry = to_ipsec_sa_entry(x);
	struct mlx5e_ipsec_modify_state_work *modify_work;
	bool need_update;

	if (!sa_entry)
		return;

	need_update = mlx5e_ipsec_update_esn_state(sa_entry);
	if (!need_update)
		return;

	modify_work = kzalloc(sizeof(*modify_work), GFP_ATOMIC);
	if (!modify_work)
		return;

	mlx5e_ipsec_build_accel_xfrm_attrs(sa_entry, &modify_work->attrs);
	modify_work->sa_entry = sa_entry;

	INIT_WORK(&modify_work->work, _update_xfrm_state);
	WARN_ON(!queue_work(sa_entry->ipsec->wq, &modify_work->work));
}