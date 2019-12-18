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
struct media_link {int /*<<< orphan*/  graph_obj; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct media_link*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_gobj_destroy (int /*<<< orphan*/ *) ; 

void __media_remove_intf_link(struct media_link *link)
{
	list_del(&link->list);
	media_gobj_destroy(&link->graph_obj);
	kfree(link);
}