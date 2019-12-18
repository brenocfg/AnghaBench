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
struct vsp1_dl_list {int has_chain; int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vsp1_dl_list_add_chain(struct vsp1_dl_list *head,
			   struct vsp1_dl_list *dl)
{
	head->has_chain = true;
	list_add_tail(&dl->chain, &head->chain);
	return 0;
}