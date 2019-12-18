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
struct its_vpe {int vpe_proxy_event; } ;
struct TYPE_2__ {size_t next_victim; int /*<<< orphan*/ ** vpes; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_send_discard (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ vpe_proxy ; 

__attribute__((used)) static void its_vpe_db_proxy_unmap_locked(struct its_vpe *vpe)
{
	/* Already unmapped? */
	if (vpe->vpe_proxy_event == -1)
		return;

	its_send_discard(vpe_proxy.dev, vpe->vpe_proxy_event);
	vpe_proxy.vpes[vpe->vpe_proxy_event] = NULL;

	/*
	 * We don't track empty slots at all, so let's move the
	 * next_victim pointer if we can quickly reuse that slot
	 * instead of nuking an existing entry. Not clear that this is
	 * always a win though, and this might just generate a ripple
	 * effect... Let's just hope VPEs don't migrate too often.
	 */
	if (vpe_proxy.vpes[vpe_proxy.next_victim])
		vpe_proxy.next_victim = vpe->vpe_proxy_event;

	vpe->vpe_proxy_event = -1;
}