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
struct ib_mad_port_private {int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 size_t rdma_max_mad_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t port_mad_size(const struct ib_mad_port_private *port_priv)
{
	return rdma_max_mad_size(port_priv->device, port_priv->port_num);
}