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
struct gsc_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 

__attribute__((used)) static int gsc_get_ratio_shift(struct gsc_context *ctx, u32 src, u32 dst,
			       u32 *ratio)
{
	DRM_DEV_DEBUG_KMS(ctx->dev, "src[%d]dst[%d]\n", src, dst);

	if (src >= dst * 8) {
		DRM_DEV_ERROR(ctx->dev, "failed to make ratio and shift.\n");
		return -EINVAL;
	} else if (src >= dst * 4)
		*ratio = 4;
	else if (src >= dst * 2)
		*ratio = 2;
	else
		*ratio = 1;

	return 0;
}