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
struct niu_rdc_tables {int first_table_num; } ;
struct niu_parent {struct niu_rdc_tables* rdc_group_cfg; } ;
struct niu {size_t port; struct niu_parent* parent; } ;

/* Variables and functions */
 int niu_num_alt_addr (struct niu*) ; 
 int niu_set_alt_mac_rdc_table (struct niu*,int,int,int) ; 
 int niu_set_multicast_mac_rdc_table (struct niu*,int,int) ; 
 int niu_set_primary_mac_rdc_table (struct niu*,int,int) ; 

__attribute__((used)) static int niu_init_hostinfo(struct niu *np)
{
	struct niu_parent *parent = np->parent;
	struct niu_rdc_tables *tp = &parent->rdc_group_cfg[np->port];
	int i, err, num_alt = niu_num_alt_addr(np);
	int first_rdc_table = tp->first_table_num;

	err = niu_set_primary_mac_rdc_table(np, first_rdc_table, 1);
	if (err)
		return err;

	err = niu_set_multicast_mac_rdc_table(np, first_rdc_table, 1);
	if (err)
		return err;

	for (i = 0; i < num_alt; i++) {
		err = niu_set_alt_mac_rdc_table(np, i, first_rdc_table, 1);
		if (err)
			return err;
	}

	return 0;
}