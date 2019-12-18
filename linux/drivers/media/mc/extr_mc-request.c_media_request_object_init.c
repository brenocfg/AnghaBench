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
struct media_request_object {int completed; int /*<<< orphan*/  kref; int /*<<< orphan*/  list; int /*<<< orphan*/ * priv; int /*<<< orphan*/ * req; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

void media_request_object_init(struct media_request_object *obj)
{
	obj->ops = NULL;
	obj->req = NULL;
	obj->priv = NULL;
	obj->completed = false;
	INIT_LIST_HEAD(&obj->list);
	kref_init(&obj->kref);
}