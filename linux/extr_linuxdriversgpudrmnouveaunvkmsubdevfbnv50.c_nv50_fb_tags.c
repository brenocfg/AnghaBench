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
struct nvkm_fb {int dummy; } ;
struct nv50_fb {int /*<<< orphan*/  base; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tags ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct nv50_fb* nv50_fb (struct nvkm_fb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
nv50_fb_tags(struct nvkm_fb *base)
{
	struct nv50_fb *fb = nv50_fb(base);
	if (fb->func->tags)
		return fb->func->tags(&fb->base);
	return 0;
}