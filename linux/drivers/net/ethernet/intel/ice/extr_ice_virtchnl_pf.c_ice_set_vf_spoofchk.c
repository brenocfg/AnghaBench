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
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sw_flags2; int /*<<< orphan*/  sec_flags; int /*<<< orphan*/  valid_sections; } ;
struct ice_vsi_ctx {TYPE_2__ info; } ;
struct TYPE_4__ {int /*<<< orphan*/  sw_flags2; int /*<<< orphan*/  sec_flags; } ;
struct ice_vsi {TYPE_1__ info; int /*<<< orphan*/  idx; struct ice_pf* back; } ;
struct ice_vf {int spoofchk; int /*<<< orphan*/  vf_states; } ;
struct ice_pf {int num_alloc_vfs; TYPE_3__* pdev; int /*<<< orphan*/  hw; struct ice_vf* vf; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQ_VSI_PROP_SECURITY_VALID ; 
 int /*<<< orphan*/  ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF ; 
 int /*<<< orphan*/  ICE_AQ_VSI_SW_FLAG_RX_PRUNE_EN_M ; 
 int /*<<< orphan*/  ICE_VF_STATE_INIT ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_vsi_ctx*) ; 
 struct ice_vsi_ctx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_update_vsi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_vsi_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ice_set_vf_spoofchk(struct net_device *netdev, int vf_id, bool ena)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	struct ice_vsi_ctx *ctx;
	enum ice_status status;
	struct ice_vf *vf;
	int ret = 0;

	/* validate the request */
	if (vf_id >= pf->num_alloc_vfs) {
		netdev_err(netdev, "invalid VF id: %d\n", vf_id);
		return -EINVAL;
	}

	vf = &pf->vf[vf_id];
	if (!test_bit(ICE_VF_STATE_INIT, vf->vf_states)) {
		netdev_err(netdev, "VF %d in reset. Try again.\n", vf_id);
		return -EBUSY;
	}

	if (ena == vf->spoofchk) {
		dev_dbg(&pf->pdev->dev, "VF spoofchk already %s\n",
			ena ? "ON" : "OFF");
		return 0;
	}

	ctx = devm_kzalloc(&pf->pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_SECURITY_VALID);

	if (ena) {
		ctx->info.sec_flags |= ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF;
		ctx->info.sw_flags2 |= ICE_AQ_VSI_SW_FLAG_RX_PRUNE_EN_M;
	}

	status = ice_update_vsi(&pf->hw, vsi->idx, ctx, NULL);
	if (status) {
		dev_dbg(&pf->pdev->dev,
			"Error %d, failed to update VSI* parameters\n", status);
		ret = -EIO;
		goto out;
	}

	vf->spoofchk = ena;
	vsi->info.sec_flags = ctx->info.sec_flags;
	vsi->info.sw_flags2 = ctx->info.sw_flags2;
out:
	devm_kfree(&pf->pdev->dev, ctx);
	return ret;
}