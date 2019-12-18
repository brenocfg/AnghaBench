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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_vsi {int /*<<< orphan*/  rss_lut_type; int /*<<< orphan*/  idx; struct ice_pf* back; } ;
struct TYPE_4__ {int /*<<< orphan*/  rq_last_status; } ;
struct ice_hw {TYPE_2__ adminq; } ;
struct ice_pf {TYPE_1__* pdev; struct ice_hw hw; } ;
struct ice_aqc_get_set_rss_keys {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int ice_aq_get_rss_key (struct ice_hw*,int /*<<< orphan*/ ,struct ice_aqc_get_set_rss_keys*) ; 
 int ice_aq_get_rss_lut (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ice_get_rss(struct ice_vsi *vsi, u8 *seed, u8 *lut, u16 lut_size)
{
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	enum ice_status status;

	if (seed) {
		struct ice_aqc_get_set_rss_keys *buf =
				  (struct ice_aqc_get_set_rss_keys *)seed;

		status = ice_aq_get_rss_key(hw, vsi->idx, buf);
		if (status) {
			dev_err(&pf->pdev->dev,
				"Cannot get RSS key, err %d aq_err %d\n",
				status, hw->adminq.rq_last_status);
			return -EIO;
		}
	}

	if (lut) {
		status = ice_aq_get_rss_lut(hw, vsi->idx, vsi->rss_lut_type,
					    lut, lut_size);
		if (status) {
			dev_err(&pf->pdev->dev,
				"Cannot get RSS lut, err %d aq_err %d\n",
				status, hw->adminq.rq_last_status);
			return -EIO;
		}
	}

	return 0;
}