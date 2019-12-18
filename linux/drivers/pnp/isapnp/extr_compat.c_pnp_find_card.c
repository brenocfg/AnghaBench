#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct list_head* next; } ;
struct pnp_card {int /*<<< orphan*/  id; TYPE_1__ global_list; } ;
struct list_head {struct list_head* next; } ;

/* Variables and functions */
 unsigned short ISAPNP_ANY_ID ; 
 scalar_t__ compare_pnp_id (int /*<<< orphan*/ ,char*) ; 
 struct pnp_card* global_to_pnp_card (struct list_head*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 struct list_head pnp_cards ; 
 int /*<<< orphan*/  pnp_convert_id (char*,unsigned short,unsigned short) ; 

struct pnp_card *pnp_find_card(unsigned short vendor, unsigned short device,
			       struct pnp_card *from)
{
	char id[8];
	char any[8];
	struct list_head *list;

	pnp_convert_id(id, vendor, device);
	pnp_convert_id(any, ISAPNP_ANY_ID, ISAPNP_ANY_ID);

	list = from ? from->global_list.next : pnp_cards.next;

	while (list != &pnp_cards) {
		struct pnp_card *card = global_to_pnp_card(list);

		if (compare_pnp_id(card->id, id) || (memcmp(id, any, 7) == 0))
			return card;
		list = list->next;
	}
	return NULL;
}