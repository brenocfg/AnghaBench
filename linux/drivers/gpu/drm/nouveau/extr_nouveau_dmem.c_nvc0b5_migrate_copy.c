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
typedef  int u64 ;
typedef  int u32 ;
struct nouveau_drm {TYPE_2__* dmem; } ;
struct nouveau_channel {int dummy; } ;
typedef  enum nouveau_aper { ____Placeholder_nouveau_aper } nouveau_aper ;
struct TYPE_3__ {struct nouveau_channel* chan; } ;
struct TYPE_4__ {TYPE_1__ migrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_IMC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int EINVAL ; 
#define  NOUVEAU_APER_HOST 129 
 int NOUVEAU_APER_VIRT ; 
#define  NOUVEAU_APER_VRAM 128 
 int /*<<< orphan*/  NvSubCopy ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int PAGE_SIZE ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int
nvc0b5_migrate_copy(struct nouveau_drm *drm, u64 npages,
		    enum nouveau_aper dst_aper, u64 dst_addr,
		    enum nouveau_aper src_aper, u64 src_addr)
{
	struct nouveau_channel *chan = drm->dmem->migrate.chan;
	u32 launch_dma = (1 << 9) /* MULTI_LINE_ENABLE. */ |
			 (1 << 8) /* DST_MEMORY_LAYOUT_PITCH. */ |
			 (1 << 7) /* SRC_MEMORY_LAYOUT_PITCH. */ |
			 (1 << 2) /* FLUSH_ENABLE_TRUE. */ |
			 (2 << 0) /* DATA_TRANSFER_TYPE_NON_PIPELINED. */;
	int ret;

	ret = RING_SPACE(chan, 13);
	if (ret)
		return ret;

	if (src_aper != NOUVEAU_APER_VIRT) {
		switch (src_aper) {
		case NOUVEAU_APER_VRAM:
			BEGIN_IMC0(chan, NvSubCopy, 0x0260, 0);
			break;
		case NOUVEAU_APER_HOST:
			BEGIN_IMC0(chan, NvSubCopy, 0x0260, 1);
			break;
		default:
			return -EINVAL;
		}
		launch_dma |= 0x00001000; /* SRC_TYPE_PHYSICAL. */
	}

	if (dst_aper != NOUVEAU_APER_VIRT) {
		switch (dst_aper) {
		case NOUVEAU_APER_VRAM:
			BEGIN_IMC0(chan, NvSubCopy, 0x0264, 0);
			break;
		case NOUVEAU_APER_HOST:
			BEGIN_IMC0(chan, NvSubCopy, 0x0264, 1);
			break;
		default:
			return -EINVAL;
		}
		launch_dma |= 0x00002000; /* DST_TYPE_PHYSICAL. */
	}

	BEGIN_NVC0(chan, NvSubCopy, 0x0400, 8);
	OUT_RING  (chan, upper_32_bits(src_addr));
	OUT_RING  (chan, lower_32_bits(src_addr));
	OUT_RING  (chan, upper_32_bits(dst_addr));
	OUT_RING  (chan, lower_32_bits(dst_addr));
	OUT_RING  (chan, PAGE_SIZE);
	OUT_RING  (chan, PAGE_SIZE);
	OUT_RING  (chan, PAGE_SIZE);
	OUT_RING  (chan, npages);
	BEGIN_NVC0(chan, NvSubCopy, 0x0300, 1);
	OUT_RING  (chan, launch_dma);
	return 0;
}