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
struct netcp_packet {int dummy; } ;
struct gbe_intf {int dummy; } ;

/* Variables and functions */
 int gbe_rxtstamp (struct gbe_intf*,struct netcp_packet*) ; 

__attribute__((used)) static int gbe_rxhook(int order, void *data, struct netcp_packet *p_info)
{
	struct gbe_intf *gbe_intf = data;

	return gbe_rxtstamp(gbe_intf, p_info);
}