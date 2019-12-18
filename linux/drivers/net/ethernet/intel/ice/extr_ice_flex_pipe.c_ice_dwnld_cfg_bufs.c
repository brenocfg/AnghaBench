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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  sq_last_status; } ;
struct ice_hw {TYPE_2__ adminq; int /*<<< orphan*/  pkg_dwnld_status; } ;
struct ice_buf_hdr {TYPE_1__* section_entry; int /*<<< orphan*/  section_count; } ;
struct ice_buf {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_RC_EEXIST ; 
 int /*<<< orphan*/  ICE_AQ_RC_OK ; 
 int /*<<< orphan*/  ICE_DBG_PKG ; 
 int ICE_ERR_AQ_NO_WORK ; 
 int ICE_ERR_PARAM ; 
 int ICE_METADATA_BUF ; 
 int /*<<< orphan*/  ICE_PKG_BUF_SIZE ; 
 int /*<<< orphan*/  ICE_RES_WRITE ; 
 int ice_acquire_global_cfg_lock (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int ice_aq_download_pkg (struct ice_hw*,struct ice_buf_hdr*,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ice_release_global_cfg_lock (struct ice_hw*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_dwnld_cfg_bufs(struct ice_hw *hw, struct ice_buf *bufs, u32 count)
{
	enum ice_status status;
	struct ice_buf_hdr *bh;
	u32 offset, info, i;

	if (!bufs || !count)
		return ICE_ERR_PARAM;

	/* If the first buffer's first section has its metadata bit set
	 * then there are no buffers to be downloaded, and the operation is
	 * considered a success.
	 */
	bh = (struct ice_buf_hdr *)bufs;
	if (le32_to_cpu(bh->section_entry[0].type) & ICE_METADATA_BUF)
		return 0;

	/* reset pkg_dwnld_status in case this function is called in the
	 * reset/rebuild flow
	 */
	hw->pkg_dwnld_status = ICE_AQ_RC_OK;

	status = ice_acquire_global_cfg_lock(hw, ICE_RES_WRITE);
	if (status) {
		if (status == ICE_ERR_AQ_NO_WORK)
			hw->pkg_dwnld_status = ICE_AQ_RC_EEXIST;
		else
			hw->pkg_dwnld_status = hw->adminq.sq_last_status;
		return status;
	}

	for (i = 0; i < count; i++) {
		bool last = ((i + 1) == count);

		if (!last) {
			/* check next buffer for metadata flag */
			bh = (struct ice_buf_hdr *)(bufs + i + 1);

			/* A set metadata flag in the next buffer will signal
			 * that the current buffer will be the last buffer
			 * downloaded
			 */
			if (le16_to_cpu(bh->section_count))
				if (le32_to_cpu(bh->section_entry[0].type) &
				    ICE_METADATA_BUF)
					last = true;
		}

		bh = (struct ice_buf_hdr *)(bufs + i);

		status = ice_aq_download_pkg(hw, bh, ICE_PKG_BUF_SIZE, last,
					     &offset, &info, NULL);

		/* Save AQ status from download package */
		hw->pkg_dwnld_status = hw->adminq.sq_last_status;
		if (status) {
			ice_debug(hw, ICE_DBG_PKG,
				  "Pkg download failed: err %d off %d inf %d\n",
				  status, offset, info);

			break;
		}

		if (last)
			break;
	}

	ice_release_global_cfg_lock(hw);

	return status;
}