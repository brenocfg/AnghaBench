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
struct nouveau_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bo_wr32 (struct nouveau_bo*,int,int) ; 

void
ovly827e_ntfy_reset(struct nouveau_bo *bo, u32 offset)
{
	nouveau_bo_wr32(bo, offset / 4 + 0, 0x00000000);
	nouveau_bo_wr32(bo, offset / 4 + 1, 0x00000000);
	nouveau_bo_wr32(bo, offset / 4 + 2, 0x00000000);
	nouveau_bo_wr32(bo, offset / 4 + 3, 0x80000000);
}