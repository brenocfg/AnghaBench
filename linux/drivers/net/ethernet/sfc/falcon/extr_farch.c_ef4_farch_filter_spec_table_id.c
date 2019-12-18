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
struct ef4_farch_filter_spec {int type; int flags; } ;
typedef  enum ef4_farch_filter_table_id { ____Placeholder_ef4_farch_filter_table_id } ef4_farch_filter_table_id ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EF4_FARCH_FILTER_MAC_FULL ; 
 int EF4_FARCH_FILTER_MAC_WILD ; 
 int EF4_FARCH_FILTER_TABLE_RX_IP ; 
 int EF4_FARCH_FILTER_TABLE_RX_MAC ; 
 int EF4_FARCH_FILTER_TABLE_TX_MAC ; 
 int EF4_FARCH_FILTER_TCP_FULL ; 
 int EF4_FARCH_FILTER_TCP_WILD ; 
 int EF4_FARCH_FILTER_UDP_FULL ; 
 int EF4_FARCH_FILTER_UDP_WILD ; 
 int EF4_FILTER_FLAG_TX ; 

__attribute__((used)) static enum ef4_farch_filter_table_id
ef4_farch_filter_spec_table_id(const struct ef4_farch_filter_spec *spec)
{
	BUILD_BUG_ON(EF4_FARCH_FILTER_TABLE_RX_IP !=
		     (EF4_FARCH_FILTER_TCP_FULL >> 2));
	BUILD_BUG_ON(EF4_FARCH_FILTER_TABLE_RX_IP !=
		     (EF4_FARCH_FILTER_TCP_WILD >> 2));
	BUILD_BUG_ON(EF4_FARCH_FILTER_TABLE_RX_IP !=
		     (EF4_FARCH_FILTER_UDP_FULL >> 2));
	BUILD_BUG_ON(EF4_FARCH_FILTER_TABLE_RX_IP !=
		     (EF4_FARCH_FILTER_UDP_WILD >> 2));
	BUILD_BUG_ON(EF4_FARCH_FILTER_TABLE_RX_MAC !=
		     (EF4_FARCH_FILTER_MAC_FULL >> 2));
	BUILD_BUG_ON(EF4_FARCH_FILTER_TABLE_RX_MAC !=
		     (EF4_FARCH_FILTER_MAC_WILD >> 2));
	BUILD_BUG_ON(EF4_FARCH_FILTER_TABLE_TX_MAC !=
		     EF4_FARCH_FILTER_TABLE_RX_MAC + 2);
	return (spec->type >> 2) + ((spec->flags & EF4_FILTER_FLAG_TX) ? 2 : 0);
}