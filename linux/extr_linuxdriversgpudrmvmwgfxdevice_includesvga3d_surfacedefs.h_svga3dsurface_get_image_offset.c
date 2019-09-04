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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  surf_size_struct ;
struct svga3d_surface_desc {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dSurfaceFormat ;

/* Variables and functions */
 struct svga3d_surface_desc* svga3dsurface_get_desc (int /*<<< orphan*/ ) ; 
 scalar_t__ svga3dsurface_get_image_buffer_size (struct svga3d_surface_desc const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svga3dsurface_get_mip_size (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32
svga3dsurface_get_image_offset(SVGA3dSurfaceFormat format,
			       surf_size_struct baseLevelSize,
			       u32 numMipLevels,
			       u32 face,
			       u32 mip)

{
	u32 offset;
	u32 mipChainBytes;
	u32 mipChainBytesToLevel;
	u32 i;
	const struct svga3d_surface_desc *desc;
	surf_size_struct mipSize;
	u32 bytes;

	desc = svga3dsurface_get_desc(format);

	mipChainBytes = 0;
	mipChainBytesToLevel = 0;
	for (i = 0; i < numMipLevels; i++) {
		mipSize = svga3dsurface_get_mip_size(baseLevelSize, i);
		bytes = svga3dsurface_get_image_buffer_size(desc, &mipSize, 0);
		mipChainBytes += bytes;
		if (i < mip)
			mipChainBytesToLevel += bytes;
	}

	offset = mipChainBytes * face + mipChainBytesToLevel;

	return offset;
}