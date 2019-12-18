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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct drm_dp_aux {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  LSPCON_PARADE_AVI_IF_CTRL ; 
 int LSPCON_PARADE_AVI_IF_KICKOFF ; 
 int /*<<< orphan*/  LSPCON_PARADE_AVI_IF_WRITE_OFFSET ; 
 scalar_t__ drm_dp_dpcd_write (struct drm_dp_aux*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  lspcon_parade_fw_ready (struct drm_dp_aux*) ; 

__attribute__((used)) static bool _lspcon_parade_write_infoframe_blocks(struct drm_dp_aux *aux,
						  u8 *avi_buf)
{
	u8 avi_if_ctrl;
	u8 block_count = 0;
	u8 *data;
	u16 reg;
	ssize_t ret;

	while (block_count < 4) {
		if (!lspcon_parade_fw_ready(aux)) {
			DRM_DEBUG_KMS("LSPCON FW not ready, block %d\n",
				      block_count);
			return false;
		}

		reg = LSPCON_PARADE_AVI_IF_WRITE_OFFSET;
		data = avi_buf + block_count * 8;
		ret = drm_dp_dpcd_write(aux, reg, data, 8);
		if (ret < 0) {
			DRM_ERROR("Failed to write AVI IF block %d\n",
				  block_count);
			return false;
		}

		/*
		 * Once a block of data is written, we have to inform the FW
		 * about this by writing into avi infoframe control register:
		 * - set the kickoff bit[7] to 1
		 * - write the block no. to bits[1:0]
		 */
		reg = LSPCON_PARADE_AVI_IF_CTRL;
		avi_if_ctrl = LSPCON_PARADE_AVI_IF_KICKOFF | block_count;
		ret = drm_dp_dpcd_write(aux, reg, &avi_if_ctrl, 1);
		if (ret < 0) {
			DRM_ERROR("Failed to update (0x%x), block %d\n",
				  reg, block_count);
			return false;
		}

		block_count++;
	}

	DRM_DEBUG_KMS("Wrote AVI IF blocks successfully\n");
	return true;
}