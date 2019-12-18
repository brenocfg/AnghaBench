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
struct macvlan_source_entry {int /*<<< orphan*/  hlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct macvlan_source_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void macvlan_hash_del_source(struct macvlan_source_entry *entry)
{
	hlist_del_rcu(&entry->hlist);
	kfree_rcu(entry, rcu);
}