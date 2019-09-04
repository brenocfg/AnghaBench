#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {TYPE_1__* agp_buffer_map; TYPE_3__* dev_private; } ;
struct drm_buf {int bus_address; int offset; int pending; scalar_t__ used; int /*<<< orphan*/  idx; TYPE_4__* dev_private; } ;
struct TYPE_7__ {TYPE_2__* sarea_priv; } ;
typedef  TYPE_3__ drm_r128_private_t ;
struct TYPE_8__ {int dispatched; int age; scalar_t__ discard; } ;
typedef  TYPE_4__ drm_r128_buf_priv_t ;
struct TYPE_6__ {int last_dispatch; } ;
struct TYPE_5__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R128_CCE_PACKET2 ; 
 int /*<<< orphan*/  R128_LAST_DISPATCH_REG ; 
 int /*<<< orphan*/  R128_PM4_IW_INDOFF ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r128_cce_dispatch_indirect(struct drm_device *dev,
				       struct drm_buf *buf, int start, int end)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	drm_r128_buf_priv_t *buf_priv = buf->dev_private;
	RING_LOCALS;
	DRM_DEBUG("indirect: buf=%d s=0x%x e=0x%x\n", buf->idx, start, end);

	if (start != end) {
		int offset = buf->bus_address + start;
		int dwords = (end - start + 3) / sizeof(u32);

		/* Indirect buffer data must be an even number of
		 * dwords, so if we've been given an odd number we must
		 * pad the data with a Type-2 CCE packet.
		 */
		if (dwords & 1) {
			u32 *data = (u32 *)
			    ((char *)dev->agp_buffer_map->handle
			     + buf->offset + start);
			data[dwords++] = cpu_to_le32(R128_CCE_PACKET2);
		}

		buf_priv->dispatched = 1;

		/* Fire off the indirect buffer */
		BEGIN_RING(3);

		OUT_RING(CCE_PACKET0(R128_PM4_IW_INDOFF, 1));
		OUT_RING(offset);
		OUT_RING(dwords);

		ADVANCE_RING();
	}

	if (buf_priv->discard) {
		buf_priv->age = dev_priv->sarea_priv->last_dispatch;

		/* Emit the indirect buffer age */
		BEGIN_RING(2);

		OUT_RING(CCE_PACKET0(R128_LAST_DISPATCH_REG, 0));
		OUT_RING(buf_priv->age);

		ADVANCE_RING();

		buf->pending = 1;
		buf->used = 0;
		/* FIXME: Check dispatched field */
		buf_priv->dispatched = 0;
	}

	dev_priv->sarea_priv->last_dispatch++;
}