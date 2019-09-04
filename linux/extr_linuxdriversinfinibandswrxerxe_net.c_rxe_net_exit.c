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
struct TYPE_2__ {int /*<<< orphan*/  sk4; int /*<<< orphan*/  sk6; } ;

/* Variables and functions */
 TYPE_1__ recv_sockets ; 
 int /*<<< orphan*/  rxe_net_notifier ; 
 int /*<<< orphan*/  rxe_release_udp_tunnel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

void rxe_net_exit(void)
{
	rxe_release_udp_tunnel(recv_sockets.sk6);
	rxe_release_udp_tunnel(recv_sockets.sk4);
	unregister_netdevice_notifier(&rxe_net_notifier);
}