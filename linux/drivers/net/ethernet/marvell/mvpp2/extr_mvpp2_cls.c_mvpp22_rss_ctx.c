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
struct mvpp2_port {int* rss_ctx; } ;

/* Variables and functions */

__attribute__((used)) static inline int mvpp22_rss_ctx(struct mvpp2_port *port, int port_rss_ctx)
{
	return port->rss_ctx[port_rss_ctx];
}