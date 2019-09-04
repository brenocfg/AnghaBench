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
struct TYPE_6__ {int y; int x; } ;
struct nv50_wndw_atom {TYPE_3__ point; } ;
struct TYPE_4__ {int /*<<< orphan*/  user; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct nv50_wndw {TYPE_2__ wimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_wr32 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
cursc37a_point(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	nvif_wr32(&wndw->wimm.base.user, 0x0208, asyw->point.y << 16 |
						 asyw->point.x);
}