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
struct vsp1_dl_list {int /*<<< orphan*/  body0; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vsp1_dl_list*) ; 
 int /*<<< orphan*/  vsp1_dl_body_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_dl_list_bodies_put (struct vsp1_dl_list*) ; 

__attribute__((used)) static void vsp1_dl_list_free(struct vsp1_dl_list *dl)
{
	vsp1_dl_body_put(dl->body0);
	vsp1_dl_list_bodies_put(dl);

	kfree(dl);
}