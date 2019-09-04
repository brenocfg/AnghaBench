#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int dither; } ;
struct TYPE_11__ {int enable; int bits; int mode; } ;
struct TYPE_8__ {int depth; } ;
struct nv50_head_atom {TYPE_6__ set; TYPE_5__ dither; TYPE_2__ base; } ;
struct TYPE_10__ {scalar_t__ mode; int depth; } ;
struct TYPE_7__ {struct drm_connector* connector; } ;
struct nouveau_conn_atom {TYPE_4__ dither; TYPE_1__ state; } ;
struct TYPE_9__ {int bpc; } ;
struct drm_connector {TYPE_3__ display_info; } ;

/* Variables and functions */
 int DITHERING_DEPTH_8BPC ; 
 int DITHERING_DEPTH_AUTO ; 
 scalar_t__ DITHERING_MODE_AUTO ; 
 int DITHERING_MODE_DYNAMIC2X2 ; 

__attribute__((used)) static void
nv50_head_atomic_check_dither(struct nv50_head_atom *armh,
			      struct nv50_head_atom *asyh,
			      struct nouveau_conn_atom *asyc)
{
	struct drm_connector *connector = asyc->state.connector;
	u32 mode = 0x00;

	if (asyc->dither.mode == DITHERING_MODE_AUTO) {
		if (asyh->base.depth > connector->display_info.bpc * 3)
			mode = DITHERING_MODE_DYNAMIC2X2;
	} else {
		mode = asyc->dither.mode;
	}

	if (asyc->dither.depth == DITHERING_DEPTH_AUTO) {
		if (connector->display_info.bpc >= 8)
			mode |= DITHERING_DEPTH_8BPC;
	} else {
		mode |= asyc->dither.depth;
	}

	asyh->dither.enable = mode;
	asyh->dither.bits = mode >> 1;
	asyh->dither.mode = mode >> 3;
	asyh->set.dither = true;
}