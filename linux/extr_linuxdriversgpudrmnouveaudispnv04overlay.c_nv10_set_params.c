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
typedef  int u32 ;
struct nvif_object {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct nouveau_plane {int brightness; int contrast; int colorkey; scalar_t__ color_encoding; int /*<<< orphan*/  flip; scalar_t__ cur; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; TYPE_3__ base; } ;
struct TYPE_5__ {struct nvif_object object; } ;
struct TYPE_6__ {TYPE_1__ device; } ;
struct TYPE_8__ {TYPE_2__ client; } ;

/* Variables and functions */
 scalar_t__ DRM_COLOR_YCBCR_BT709 ; 
 int /*<<< orphan*/  NV_PVIDEO_CHROMINANCE (int) ; 
 int /*<<< orphan*/  NV_PVIDEO_COLOR_KEY ; 
 int /*<<< orphan*/  NV_PVIDEO_FORMAT (int /*<<< orphan*/ ) ; 
 int NV_PVIDEO_FORMAT_DISPLAY_COLOR_KEY ; 
 int NV_PVIDEO_FORMAT_MATRIX_ITURBT709 ; 
 int /*<<< orphan*/  NV_PVIDEO_LUMINANCE (int) ; 
 int cos_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_mask (struct nvif_object*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvif_wr32 (struct nvif_object*,int /*<<< orphan*/ ,int) ; 
 int sin_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv10_set_params(struct nouveau_plane *plane)
{
	struct nvif_object *dev = &nouveau_drm(plane->base.dev)->client.device.object;
	u32 luma = (plane->brightness - 512) << 16 | plane->contrast;
	u32 chroma = ((sin_mul(plane->hue, plane->saturation) & 0xffff) << 16) |
		(cos_mul(plane->hue, plane->saturation) & 0xffff);
	u32 format = 0;

	nvif_wr32(dev, NV_PVIDEO_LUMINANCE(0), luma);
	nvif_wr32(dev, NV_PVIDEO_LUMINANCE(1), luma);
	nvif_wr32(dev, NV_PVIDEO_CHROMINANCE(0), chroma);
	nvif_wr32(dev, NV_PVIDEO_CHROMINANCE(1), chroma);
	nvif_wr32(dev, NV_PVIDEO_COLOR_KEY, plane->colorkey & 0xffffff);

	if (plane->cur) {
		if (plane->color_encoding == DRM_COLOR_YCBCR_BT709)
			format |= NV_PVIDEO_FORMAT_MATRIX_ITURBT709;
		if (plane->colorkey & (1 << 24))
			format |= NV_PVIDEO_FORMAT_DISPLAY_COLOR_KEY;
		nvif_mask(dev, NV_PVIDEO_FORMAT(plane->flip),
			NV_PVIDEO_FORMAT_MATRIX_ITURBT709 |
			NV_PVIDEO_FORMAT_DISPLAY_COLOR_KEY,
			format);
	}
}