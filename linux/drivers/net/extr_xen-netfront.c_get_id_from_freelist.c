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
union skb_entry {unsigned int link; } ;

/* Variables and functions */

__attribute__((used)) static unsigned short get_id_from_freelist(unsigned *head,
					   union skb_entry *list)
{
	unsigned int id = *head;
	*head = list[id].link;
	return id;
}