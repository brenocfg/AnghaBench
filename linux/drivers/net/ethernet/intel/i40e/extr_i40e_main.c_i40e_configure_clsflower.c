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
struct i40e_vsi {struct i40e_pf* back; int /*<<< orphan*/  netdev; } ;
struct i40e_pf {int flags; int /*<<< orphan*/  num_cloud_filters; int /*<<< orphan*/  cloud_filter_list; int /*<<< orphan*/  hw; TYPE_1__* pdev; int /*<<< orphan*/  fdir_filter_list; scalar_t__ fdir_pf_active_filters; int /*<<< orphan*/  state; } ;
struct i40e_cloud_filter {int /*<<< orphan*/  cloud_node; scalar_t__ dst_port; int /*<<< orphan*/  cookie; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; int /*<<< orphan*/  classid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I40E_FLAG_FD_SB_ENABLED ; 
 int I40E_FLAG_FD_SB_TO_CLOUD_FILTER ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __I40E_RESET_INTR_RECEIVED ; 
 int /*<<< orphan*/  __I40E_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int i40e_add_del_cloud_filter (struct i40e_vsi*,struct i40e_cloud_filter*,int) ; 
 int i40e_add_del_cloud_filter_big_buf (struct i40e_vsi*,struct i40e_cloud_filter*,int) ; 
 int i40e_handle_tclass (struct i40e_vsi*,int,struct i40e_cloud_filter*) ; 
 int i40e_parse_cls_flower (struct i40e_vsi*,struct flow_cls_offload*,struct i40e_cloud_filter*) ; 
 int /*<<< orphan*/  i40e_stat_str (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct i40e_cloud_filter*) ; 
 struct i40e_cloud_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int tc_classid_to_hwtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_configure_clsflower(struct i40e_vsi *vsi,
				    struct flow_cls_offload *cls_flower)
{
	int tc = tc_classid_to_hwtc(vsi->netdev, cls_flower->classid);
	struct i40e_cloud_filter *filter = NULL;
	struct i40e_pf *pf = vsi->back;
	int err = 0;

	if (tc < 0) {
		dev_err(&vsi->back->pdev->dev, "Invalid traffic class\n");
		return -EOPNOTSUPP;
	}

	if (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
	    test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
		return -EBUSY;

	if (pf->fdir_pf_active_filters ||
	    (!hlist_empty(&pf->fdir_filter_list))) {
		dev_err(&vsi->back->pdev->dev,
			"Flow Director Sideband filters exists, turn ntuple off to configure cloud filters\n");
		return -EINVAL;
	}

	if (vsi->back->flags & I40E_FLAG_FD_SB_ENABLED) {
		dev_err(&vsi->back->pdev->dev,
			"Disable Flow Director Sideband, configuring Cloud filters via tc-flower\n");
		vsi->back->flags &= ~I40E_FLAG_FD_SB_ENABLED;
		vsi->back->flags |= I40E_FLAG_FD_SB_TO_CLOUD_FILTER;
	}

	filter = kzalloc(sizeof(*filter), GFP_KERNEL);
	if (!filter)
		return -ENOMEM;

	filter->cookie = cls_flower->cookie;

	err = i40e_parse_cls_flower(vsi, cls_flower, filter);
	if (err < 0)
		goto err;

	err = i40e_handle_tclass(vsi, tc, filter);
	if (err < 0)
		goto err;

	/* Add cloud filter */
	if (filter->dst_port)
		err = i40e_add_del_cloud_filter_big_buf(vsi, filter, true);
	else
		err = i40e_add_del_cloud_filter(vsi, filter, true);

	if (err) {
		dev_err(&pf->pdev->dev,
			"Failed to add cloud filter, err %s\n",
			i40e_stat_str(&pf->hw, err));
		goto err;
	}

	/* add filter to the ordered list */
	INIT_HLIST_NODE(&filter->cloud_node);

	hlist_add_head(&filter->cloud_node, &pf->cloud_filter_list);

	pf->num_cloud_filters++;

	return err;
err:
	kfree(filter);
	return err;
}