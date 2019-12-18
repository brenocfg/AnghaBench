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
typedef  int u32 ;
struct mvpp2_port {scalar_t__* rss_ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 int MVPP22_N_RSS_TABLES ; 
 int mvpp22_rss_context_create (struct mvpp2_port*,int*) ; 

int mvpp22_port_rss_ctx_create(struct mvpp2_port *port, u32 *port_ctx)
{
	u32 rss_ctx;
	int ret, i;

	ret = mvpp22_rss_context_create(port, &rss_ctx);
	if (ret)
		return ret;

	/* Find the first available context number in the port, starting from 1.
	 * Context 0 on each port is reserved for the default context.
	 */
	for (i = 1; i < MVPP22_N_RSS_TABLES; i++) {
		if (port->rss_ctx[i] < 0)
			break;
	}

	if (i == MVPP22_N_RSS_TABLES)
		return -EINVAL;

	port->rss_ctx[i] = rss_ctx;
	*port_ctx = i;

	return 0;
}