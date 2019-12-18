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
struct TYPE_2__ {int /*<<< orphan*/  (* set_pos ) (struct nouveau_crtc*,int,int) ;} ;
struct nouveau_crtc {TYPE_1__ cursor; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_crtc*,int,int) ; 

__attribute__((used)) static int
nv04_crtc_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	nv_crtc->cursor.set_pos(nv_crtc, x, y);
	return 0;
}