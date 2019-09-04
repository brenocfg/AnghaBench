#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct nouveau_channel {TYPE_3__ vram; TYPE_2__* drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {TYPE_1__ ntfy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NvSubCopy ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int /*<<< orphan*/ ) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 

__attribute__((used)) static int
nv50_bo_move_init(struct nouveau_channel *chan, u32 handle)
{
	int ret = RING_SPACE(chan, 6);
	if (ret == 0) {
		BEGIN_NV04(chan, NvSubCopy, 0x0000, 1);
		OUT_RING  (chan, handle);
		BEGIN_NV04(chan, NvSubCopy, 0x0180, 3);
		OUT_RING  (chan, chan->drm->ntfy.handle);
		OUT_RING  (chan, chan->vram.handle);
		OUT_RING  (chan, chan->vram.handle);
	}

	return ret;
}