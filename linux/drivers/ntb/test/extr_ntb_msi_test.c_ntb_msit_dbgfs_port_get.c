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
typedef  int /*<<< orphan*/  u64 ;
struct ntb_msit_peer {int /*<<< orphan*/  pidx; TYPE_1__* nm; } ;
struct TYPE_2__ {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntb_peer_port_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntb_msit_dbgfs_port_get(void *data, u64 *port)
{
	struct ntb_msit_peer *peer = data;

	*port = ntb_peer_port_number(peer->nm->ntb, peer->pidx);

	return 0;
}