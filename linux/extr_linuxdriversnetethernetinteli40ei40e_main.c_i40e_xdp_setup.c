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
struct i40e_vsi {int rx_buf_len; int num_queue_pairs; int /*<<< orphan*/  xdp_prog; TYPE_2__** rx_rings; struct i40e_pf* back; TYPE_1__* netdev; } ;
struct i40e_pf {int dummy; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  xdp_prog; } ;
struct TYPE_3__ {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_prep_for_reset (struct i40e_pf*,int) ; 
 int /*<<< orphan*/  i40e_reset_and_rebuild (struct i40e_pf*,int,int) ; 
 struct bpf_prog* xchg (int /*<<< orphan*/ *,struct bpf_prog*) ; 

__attribute__((used)) static int i40e_xdp_setup(struct i40e_vsi *vsi,
			  struct bpf_prog *prog)
{
	int frame_size = vsi->netdev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	struct i40e_pf *pf = vsi->back;
	struct bpf_prog *old_prog;
	bool need_reset;
	int i;

	/* Don't allow frames that span over multiple buffers */
	if (frame_size > vsi->rx_buf_len)
		return -EINVAL;

	if (!i40e_enabled_xdp_vsi(vsi) && !prog)
		return 0;

	/* When turning XDP on->off/off->on we reset and rebuild the rings. */
	need_reset = (i40e_enabled_xdp_vsi(vsi) != !!prog);

	if (need_reset)
		i40e_prep_for_reset(pf, true);

	old_prog = xchg(&vsi->xdp_prog, prog);

	if (need_reset)
		i40e_reset_and_rebuild(pf, true, true);

	for (i = 0; i < vsi->num_queue_pairs; i++)
		WRITE_ONCE(vsi->rx_rings[i]->xdp_prog, vsi->xdp_prog);

	if (old_prog)
		bpf_prog_put(old_prog);

	return 0;
}