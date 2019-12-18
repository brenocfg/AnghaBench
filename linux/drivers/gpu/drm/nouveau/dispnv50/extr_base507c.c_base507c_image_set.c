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
struct TYPE_2__ {int mode; int interval; int* handle; int format; int* offset; int h; int w; int layout; int* pitch; int* blocks; int blockh; int kind; } ;
struct nv50_wndw_atom {TYPE_1__ image; } ;
struct nv50_wndw {int /*<<< orphan*/  wndw; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
base507c_image_set(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	u32 *push;
	if ((push = evo_wait(&wndw->wndw, 13))) {
		evo_mthd(push, 0x0084, 1);
		evo_data(push, asyw->image.mode << 8 |
			       asyw->image.interval << 4);
		evo_mthd(push, 0x00c0, 1);
		evo_data(push, asyw->image.handle[0]);
		if (asyw->image.format == 0xca) {
			evo_mthd(push, 0x0110, 2);
			evo_data(push, 1);
			evo_data(push, 0x6400);
		} else {
			evo_mthd(push, 0x0110, 2);
			evo_data(push, 0);
			evo_data(push, 0);
		}
		evo_mthd(push, 0x0800, 5);
		evo_data(push, asyw->image.offset[0] >> 8);
		evo_data(push, 0x00000000);
		evo_data(push, asyw->image.h << 16 | asyw->image.w);
		evo_data(push, asyw->image.layout << 20 |
			       (asyw->image.pitch[0] >> 8) << 8 |
			       asyw->image.blocks[0] << 8 |
			       asyw->image.blockh);
		evo_data(push, asyw->image.kind << 16 |
			       asyw->image.format << 8);
		evo_kick(push, &wndw->wndw);
	}
}