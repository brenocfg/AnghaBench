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
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NvSubCopy ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 

__attribute__((used)) static int
nve0_bo_move_init(struct nouveau_channel *chan, u32 handle)
{
	int ret = RING_SPACE(chan, 2);
	if (ret == 0) {
		BEGIN_NVC0(chan, NvSubCopy, 0x0000, 1);
		OUT_RING  (chan, handle & 0x0000ffff);
		FIRE_RING (chan);
	}
	return ret;
}