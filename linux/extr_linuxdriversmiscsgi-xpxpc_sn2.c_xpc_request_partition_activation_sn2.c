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
struct xpc_rsvd_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpc_send_local_activate_IRQ_sn2 (int) ; 

__attribute__((used)) static void
xpc_request_partition_activation_sn2(struct xpc_rsvd_page *remote_rp,
				     unsigned long remote_rp_pa, int nasid)
{
	xpc_send_local_activate_IRQ_sn2(nasid);
}