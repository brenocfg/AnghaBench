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
struct nv50_wndw {int dummy; } ;
struct nouveau_drm {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ovly507e ; 
 int /*<<< orphan*/  ovly507e_format ; 
 int ovly507e_new_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nouveau_drm*,int,int /*<<< orphan*/ ,int,struct nv50_wndw**) ; 

int
ovly507e_new(struct nouveau_drm *drm, int head, s32 oclass,
	     struct nv50_wndw **pwndw)
{
	return ovly507e_new_(&ovly507e, ovly507e_format, drm, head, oclass,
			     0x00000004 << (head * 8), pwndw);
}