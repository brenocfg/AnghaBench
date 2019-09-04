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
struct qede_dev {TYPE_1__* arfs; } ;
struct qede_arfs_tuple {scalar_t__ mode; } ;
struct ethtool_rx_flow_spec {scalar_t__ location; scalar_t__ ring_cookie; } ;
struct TYPE_2__ {scalar_t__ mode; scalar_t__ filter_count; int /*<<< orphan*/  arfs_fltr_bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*,...) ; 
 int EINVAL ; 
 scalar_t__ QEDE_RFS_MAX_FLTR ; 
 scalar_t__ QEDE_RSS_COUNT (struct qede_dev*) ; 
 scalar_t__ RX_CLS_FLOW_DISC ; 
 scalar_t__ ethtool_get_flow_spec_ring_vf (scalar_t__) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_flow_spec_validate(struct qede_dev *edev,
				   struct ethtool_rx_flow_spec *fs,
				   struct qede_arfs_tuple *t)
{
	if (fs->location >= QEDE_RFS_MAX_FLTR) {
		DP_INFO(edev, "Location out-of-bounds\n");
		return -EINVAL;
	}

	/* Check location isn't already in use */
	if (test_bit(fs->location, edev->arfs->arfs_fltr_bmap)) {
		DP_INFO(edev, "Location already in use\n");
		return -EINVAL;
	}

	/* Check if the filtering-mode could support the filter */
	if (edev->arfs->filter_count &&
	    edev->arfs->mode != t->mode) {
		DP_INFO(edev,
			"flow_spec would require filtering mode %08x, but %08x is configured\n",
			t->mode, edev->arfs->filter_count);
		return -EINVAL;
	}

	/* If drop requested then no need to validate other data */
	if (fs->ring_cookie == RX_CLS_FLOW_DISC)
		return 0;

	if (ethtool_get_flow_spec_ring_vf(fs->ring_cookie))
		return 0;

	if (fs->ring_cookie >= QEDE_RSS_COUNT(edev)) {
		DP_INFO(edev, "Queue out-of-bounds\n");
		return -EINVAL;
	}

	return 0;
}