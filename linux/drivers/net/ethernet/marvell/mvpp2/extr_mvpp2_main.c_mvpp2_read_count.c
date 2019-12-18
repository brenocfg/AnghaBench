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
typedef  int u64 ;
struct mvpp2_port {scalar_t__ stats_base; } ;
struct mvpp2_ethtool_counter {scalar_t__ offset; scalar_t__ reg_is_64b; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 

__attribute__((used)) static u64 mvpp2_read_count(struct mvpp2_port *port,
			    const struct mvpp2_ethtool_counter *counter)
{
	u64 val;

	val = readl(port->stats_base + counter->offset);
	if (counter->reg_is_64b)
		val += (u64)readl(port->stats_base + counter->offset + 4) << 32;

	return val;
}