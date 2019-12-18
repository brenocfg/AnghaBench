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
struct ice_pkg_hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  draft; int /*<<< orphan*/  update; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_3__ {int /*<<< orphan*/  draft; int /*<<< orphan*/  update; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct ice_hw {int /*<<< orphan*/  ice_pkg_name; TYPE_2__ ice_pkg_ver; int /*<<< orphan*/  pkg_name; TYPE_1__ pkg_ver; } ;
struct ice_global_metadata_seg {int /*<<< orphan*/  pkg_name; TYPE_1__ pkg_ver; } ;
struct ice_generic_seg_hdr {int /*<<< orphan*/  seg_name; TYPE_2__ seg_ver; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_INIT ; 
 int /*<<< orphan*/  ICE_DBG_PKG ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  SEGMENT_TYPE_ICE ; 
 int /*<<< orphan*/  SEGMENT_TYPE_METADATA ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,...) ; 
 struct ice_generic_seg_hdr* ice_find_seg_in_pkg (struct ice_hw*,int /*<<< orphan*/ ,struct ice_pkg_hdr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum ice_status
ice_init_pkg_info(struct ice_hw *hw, struct ice_pkg_hdr *pkg_hdr)
{
	struct ice_global_metadata_seg *meta_seg;
	struct ice_generic_seg_hdr *seg_hdr;

	if (!pkg_hdr)
		return ICE_ERR_PARAM;

	meta_seg = (struct ice_global_metadata_seg *)
		   ice_find_seg_in_pkg(hw, SEGMENT_TYPE_METADATA, pkg_hdr);
	if (meta_seg) {
		hw->pkg_ver = meta_seg->pkg_ver;
		memcpy(hw->pkg_name, meta_seg->pkg_name, sizeof(hw->pkg_name));

		ice_debug(hw, ICE_DBG_PKG, "Pkg: %d.%d.%d.%d, %s\n",
			  meta_seg->pkg_ver.major, meta_seg->pkg_ver.minor,
			  meta_seg->pkg_ver.update, meta_seg->pkg_ver.draft,
			  meta_seg->pkg_name);
	} else {
		ice_debug(hw, ICE_DBG_INIT,
			  "Did not find metadata segment in driver package\n");
		return ICE_ERR_CFG;
	}

	seg_hdr = ice_find_seg_in_pkg(hw, SEGMENT_TYPE_ICE, pkg_hdr);
	if (seg_hdr) {
		hw->ice_pkg_ver = seg_hdr->seg_ver;
		memcpy(hw->ice_pkg_name, seg_hdr->seg_name,
		       sizeof(hw->ice_pkg_name));

		ice_debug(hw, ICE_DBG_PKG, "Ice Pkg: %d.%d.%d.%d, %s\n",
			  seg_hdr->seg_ver.major, seg_hdr->seg_ver.minor,
			  seg_hdr->seg_ver.update, seg_hdr->seg_ver.draft,
			  seg_hdr->seg_name);
	} else {
		ice_debug(hw, ICE_DBG_INIT,
			  "Did not find ice segment in driver package\n");
		return ICE_ERR_CFG;
	}

	return 0;
}