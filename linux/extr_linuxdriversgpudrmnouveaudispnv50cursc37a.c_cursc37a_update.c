#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  user; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct nv50_wndw {TYPE_2__ wimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_wr32 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
cursc37a_update(struct nv50_wndw *wndw, u32 *interlock)
{
	nvif_wr32(&wndw->wimm.base.user, 0x0200, 0x00000001);
}