#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nv84_fence_priv {int /*<<< orphan*/  bo; } ;
struct nouveau_channel {int chid; TYPE_1__* drm; } ;
struct TYPE_2__ {struct nv84_fence_priv* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bo_rd32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
nv84_fence_read(struct nouveau_channel *chan)
{
	struct nv84_fence_priv *priv = chan->drm->fence;
	return nouveau_bo_rd32(priv->bo, chan->chid * 16/4);
}