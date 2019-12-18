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
struct TYPE_2__ {int /*<<< orphan*/ * sk4; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ROCE_V2_UDP_DPORT ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ recv_sockets ; 
 int /*<<< orphan*/ * rxe_setup_udp_tunnel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rxe_net_ipv4_init(void)
{
	recv_sockets.sk4 = rxe_setup_udp_tunnel(&init_net,
				htons(ROCE_V2_UDP_DPORT), false);
	if (IS_ERR(recv_sockets.sk4)) {
		recv_sockets.sk4 = NULL;
		pr_err("Failed to create IPv4 UDP tunnel\n");
		return -1;
	}

	return 0;
}