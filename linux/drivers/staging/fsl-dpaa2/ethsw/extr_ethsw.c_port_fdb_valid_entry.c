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
struct fdb_dump_entry {int type; int if_info; int* if_mask; } ;
struct ethsw_port_priv {int idx; } ;

/* Variables and functions */
 int BIT (int) ; 
 int DPSW_FDB_ENTRY_TYPE_UNICAST ; 

__attribute__((used)) static int port_fdb_valid_entry(struct fdb_dump_entry *entry,
				struct ethsw_port_priv *port_priv)
{
	int idx = port_priv->idx;
	int valid;

	if (entry->type & DPSW_FDB_ENTRY_TYPE_UNICAST)
		valid = entry->if_info == port_priv->idx;
	else
		valid = entry->if_mask[idx / 8] & BIT(idx % 8);

	return valid;
}