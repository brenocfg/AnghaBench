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
struct mvpp2_port {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ mvpp22_rss_ctx (struct mvpp2_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_rss_port_c2_enable (struct mvpp2_port*,scalar_t__) ; 

int mvpp22_port_rss_enable(struct mvpp2_port *port)
{
	if (mvpp22_rss_ctx(port, 0) < 0)
		return -EINVAL;

	mvpp2_rss_port_c2_enable(port, mvpp22_rss_ctx(port, 0));

	return 0;
}