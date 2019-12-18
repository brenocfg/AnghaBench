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
typedef  int u32 ;
struct gsc_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int GSC_MAX_DST ; 
 int /*<<< orphan*/  GSC_OUT_BASE_ADDR_Y_MASK ; 
 int GSC_OUT_CURR_GET_INDEX (int) ; 
 int /*<<< orphan*/  gsc_dst_set_buf_seq (struct gsc_context*,int,int) ; 
 int gsc_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gsc_get_dst_buf_index(struct gsc_context *ctx)
{
	u32 cfg, curr_index, i;
	u32 buf_id = GSC_MAX_DST;

	DRM_DEV_DEBUG_KMS(ctx->dev, "gsc id[%d]\n", ctx->id);

	cfg = gsc_read(GSC_OUT_BASE_ADDR_Y_MASK);
	curr_index = GSC_OUT_CURR_GET_INDEX(cfg);

	for (i = curr_index; i < GSC_MAX_DST; i++) {
		if (!((cfg >> i) & 0x1)) {
			buf_id = i;
			break;
		}
	}

	if (buf_id == GSC_MAX_DST) {
		DRM_DEV_ERROR(ctx->dev, "failed to get out buffer index.\n");
		return -EINVAL;
	}

	gsc_dst_set_buf_seq(ctx, buf_id, false);

	DRM_DEV_DEBUG_KMS(ctx->dev, "cfg[0x%x]curr_index[%d]buf_id[%d]\n", cfg,
			  curr_index, buf_id);

	return buf_id;
}