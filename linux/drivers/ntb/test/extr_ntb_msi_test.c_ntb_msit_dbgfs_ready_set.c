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
typedef  int /*<<< orphan*/  u64 ;
struct ntb_msit_peer {int /*<<< orphan*/  init_comp; } ;

/* Variables and functions */
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ntb_msit_dbgfs_ready_set(void *data, u64 ready)
{
	struct ntb_msit_peer *peer = data;

	return wait_for_completion_interruptible(&peer->init_comp);
}