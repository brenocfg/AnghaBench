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
struct usif_object {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usif_object*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usif_object_dtor(struct usif_object *object)
{
	list_del(&object->head);
	kfree(object);
}