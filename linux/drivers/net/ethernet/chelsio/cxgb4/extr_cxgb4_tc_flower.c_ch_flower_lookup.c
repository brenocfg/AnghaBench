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
struct ch_tc_flower_entry {int dummy; } ;
struct adapter {int /*<<< orphan*/  flower_ht_params; int /*<<< orphan*/  flower_tbl; } ;

/* Variables and functions */
 struct ch_tc_flower_entry* rhashtable_lookup_fast (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ch_tc_flower_entry *ch_flower_lookup(struct adapter *adap,
						   unsigned long flower_cookie)
{
	return rhashtable_lookup_fast(&adap->flower_tbl, &flower_cookie,
				      adap->flower_ht_params);
}