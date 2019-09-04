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
struct nv50_core {int dummy; } ;
struct nouveau_drm {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int core507d_new_ (int /*<<< orphan*/ *,struct nouveau_drm*,int /*<<< orphan*/ ,struct nv50_core**) ; 
 int /*<<< orphan*/  core907d ; 

int
core907d_new(struct nouveau_drm *drm, s32 oclass, struct nv50_core **pcore)
{
	return core507d_new_(&core907d, drm, oclass, pcore);
}