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
 int /*<<< orphan*/  GSC_IN_BASE_ADDR_Y_MASK ; 
 int GSC_IN_CURR_GET_INDEX (int) ; 
 int GSC_MAX_SRC ; 
 int gsc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_src_set_buf_seq (struct gsc_context*,int,int) ; 

__attribute__((used)) static int gsc_get_src_buf_index(struct gsc_context *ctx)
{
	u32 cfg, curr_index, i;
	u32 buf_id = GSC_MAX_SRC;

	DRM_DEV_DEBUG_KMS(ctx->dev, "gsc id[%d]\n", ctx->id);

	cfg = gsc_read(GSC_IN_BASE_ADDR_Y_MASK);
	curr_index = GSC_IN_CURR_GET_INDEX(cfg);

	for (i = curr_index; i < GSC_MAX_SRC; i++) {
		if (!((cfg >> i) & 0x1)) {
			buf_id = i;
			break;
		}
	}

	DRM_DEV_DEBUG_KMS(ctx->dev, "cfg[0x%x]curr_index[%d]buf_id[%d]\n", cfg,
			  curr_index, buf_id);

	if (buf_id == GSC_MAX_SRC) {
		DRM_DEV_ERROR(ctx->dev, "failed to get in buffer index.\n");
		return -EINVAL;
	}

	gsc_src_set_buf_seq(ctx, buf_id, false);

	return buf_id;
}