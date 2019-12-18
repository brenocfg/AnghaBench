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
struct vhost_net {int /*<<< orphan*/  tx_zcopy_err; } ;

/* Variables and functions */

__attribute__((used)) static void vhost_net_tx_err(struct vhost_net *net)
{
	++net->tx_zcopy_err;
}