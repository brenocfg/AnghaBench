#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ next; } ;
struct TYPE_4__ {TYPE_1__ entries; } ;
struct overlay_changeset {int count; struct overlay_changeset* fdt; struct overlay_changeset* overlay_tree; struct overlay_changeset* fragments; int /*<<< orphan*/  overlay; int /*<<< orphan*/  target; scalar_t__ id; TYPE_2__ cset; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct overlay_changeset*) ; 
 int /*<<< orphan*/  of_changeset_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovcs_idr ; 

__attribute__((used)) static void free_overlay_changeset(struct overlay_changeset *ovcs)
{
	int i;

	if (ovcs->cset.entries.next)
		of_changeset_destroy(&ovcs->cset);

	if (ovcs->id)
		idr_remove(&ovcs_idr, ovcs->id);

	for (i = 0; i < ovcs->count; i++) {
		of_node_put(ovcs->fragments[i].target);
		of_node_put(ovcs->fragments[i].overlay);
	}
	kfree(ovcs->fragments);
	/*
	 * There should be no live pointers into ovcs->overlay_tree and
	 * ovcs->fdt due to the policy that overlay notifiers are not allowed
	 * to retain pointers into the overlay devicetree.
	 */
	kfree(ovcs->overlay_tree);
	kfree(ovcs->fdt);
	kfree(ovcs);
}