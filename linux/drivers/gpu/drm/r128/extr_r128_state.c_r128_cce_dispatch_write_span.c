#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  y ;
typedef  int /*<<< orphan*/  x ;
typedef  int u8 ;
typedef  int u32 ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {int depth_fmt; int depth_pitch_offset_c; } ;
typedef  TYPE_1__ drm_r128_private_t ;
struct TYPE_5__ {int n; scalar_t__ mask; scalar_t__ buffer; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ drm_r128_depth_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EFAULT ; 
 int EMSGSIZE ; 
 scalar_t__ IS_ERR (int*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int PTR_ERR (int*) ; 
 int /*<<< orphan*/  R128_CNTL_PAINT_MULTI ; 
 int R128_GMC_BRUSH_SOLID_COLOR ; 
 int R128_GMC_CLR_CMP_CNTL_DIS ; 
 int R128_GMC_DST_PITCH_OFFSET_CNTL ; 
 int R128_GMC_SRC_DATATYPE_COLOR ; 
 int R128_GMC_WR_MSK_DIS ; 
 int R128_ROP3_P ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 scalar_t__ copy_from_user (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* memdup_user (scalar_t__,int) ; 

__attribute__((used)) static int r128_cce_dispatch_write_span(struct drm_device *dev,
					drm_r128_depth_t *depth)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	int count, x, y;
	u32 *buffer;
	u8 *mask;
	int i, buffer_size, mask_size;
	RING_LOCALS;
	DRM_DEBUG("\n");

	count = depth->n;
	if (count > 4096 || count <= 0)
		return -EMSGSIZE;

	if (copy_from_user(&x, depth->x, sizeof(x)))
		return -EFAULT;
	if (copy_from_user(&y, depth->y, sizeof(y)))
		return -EFAULT;

	buffer_size = depth->n * sizeof(u32);
	buffer = memdup_user(depth->buffer, buffer_size);
	if (IS_ERR(buffer))
		return PTR_ERR(buffer);

	mask_size = depth->n;
	if (depth->mask) {
		mask = memdup_user(depth->mask, mask_size);
		if (IS_ERR(mask)) {
			kfree(buffer);
			return PTR_ERR(mask);
		}

		for (i = 0; i < count; i++, x++) {
			if (mask[i]) {
				BEGIN_RING(6);

				OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
				OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
					 R128_GMC_BRUSH_SOLID_COLOR |
					 (dev_priv->depth_fmt << 8) |
					 R128_GMC_SRC_DATATYPE_COLOR |
					 R128_ROP3_P |
					 R128_GMC_CLR_CMP_CNTL_DIS |
					 R128_GMC_WR_MSK_DIS);

				OUT_RING(dev_priv->depth_pitch_offset_c);
				OUT_RING(buffer[i]);

				OUT_RING((x << 16) | y);
				OUT_RING((1 << 16) | 1);

				ADVANCE_RING();
			}
		}

		kfree(mask);
	} else {
		for (i = 0; i < count; i++, x++) {
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->depth_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_WR_MSK_DIS);

			OUT_RING(dev_priv->depth_pitch_offset_c);
			OUT_RING(buffer[i]);

			OUT_RING((x << 16) | y);
			OUT_RING((1 << 16) | 1);

			ADVANCE_RING();
		}
	}

	kfree(buffer);

	return 0;
}