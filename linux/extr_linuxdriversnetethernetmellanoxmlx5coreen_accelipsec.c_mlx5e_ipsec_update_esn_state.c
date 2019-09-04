#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct xfrm_replay_state_esn {scalar_t__ seq; scalar_t__ replay_window; } ;
struct TYPE_5__ {int trigger; int overlap; scalar_t__ esn; } ;
struct mlx5e_ipsec_sa_entry {TYPE_2__ esn_state; TYPE_3__* x; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_6__ {struct xfrm_replay_state_esn* replay_esn; TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ MLX5E_IPSEC_ESN_SCOPE_MID ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xfrm_replay_seqhi (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mlx5e_ipsec_update_esn_state(struct mlx5e_ipsec_sa_entry *sa_entry)
{
	struct xfrm_replay_state_esn *replay_esn;
	u32 seq_bottom;
	u8 overlap;
	u32 *esn;

	if (!(sa_entry->x->props.flags & XFRM_STATE_ESN)) {
		sa_entry->esn_state.trigger = 0;
		return false;
	}

	replay_esn = sa_entry->x->replay_esn;
	seq_bottom = replay_esn->seq - replay_esn->replay_window + 1;
	overlap = sa_entry->esn_state.overlap;

	sa_entry->esn_state.esn = xfrm_replay_seqhi(sa_entry->x,
						    htonl(seq_bottom));
	esn = &sa_entry->esn_state.esn;

	sa_entry->esn_state.trigger = 1;
	if (unlikely(overlap && seq_bottom < MLX5E_IPSEC_ESN_SCOPE_MID)) {
		++(*esn);
		sa_entry->esn_state.overlap = 0;
		return true;
	} else if (unlikely(!overlap &&
			    (seq_bottom >= MLX5E_IPSEC_ESN_SCOPE_MID))) {
		sa_entry->esn_state.overlap = 1;
		return true;
	}

	return false;
}