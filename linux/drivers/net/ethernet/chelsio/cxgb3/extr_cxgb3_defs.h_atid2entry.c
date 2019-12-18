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
typedef  union active_open_entry {int dummy; } active_open_entry ;
struct tid_info {unsigned int atid_base; union active_open_entry* atid_tab; } ;

/* Variables and functions */

__attribute__((used)) static inline union active_open_entry *atid2entry(const struct tid_info *t,
						  unsigned int atid)
{
	return &t->atid_tab[atid - t->atid_base];
}