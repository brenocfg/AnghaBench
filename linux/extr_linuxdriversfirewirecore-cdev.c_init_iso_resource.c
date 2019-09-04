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
struct TYPE_4__ {int handle; int /*<<< orphan*/ * release; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  closure; } ;
struct iso_resource_event {int todo; int generation; scalar_t__ channels; scalar_t__ bandwidth; TYPE_2__ resource; TYPE_1__ iso_resource; struct iso_resource_event* e_dealloc; struct iso_resource_event* e_alloc; struct client* client; int /*<<< orphan*/  work; } ;
struct iso_resource {int todo; int generation; scalar_t__ channels; scalar_t__ bandwidth; TYPE_2__ resource; TYPE_1__ iso_resource; struct iso_resource* e_dealloc; struct iso_resource* e_alloc; struct client* client; int /*<<< orphan*/  work; } ;
struct fw_cdev_allocate_iso_resource {scalar_t__ channels; scalar_t__ bandwidth; int handle; int /*<<< orphan*/  closure; } ;
struct client {int dummy; } ;

/* Variables and functions */
 scalar_t__ BANDWIDTH_AVAILABLE_INITIAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED ; 
 int /*<<< orphan*/  FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ISO_RES_ALLOC ; 
 int add_client_resource (struct client*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iso_resource_work ; 
 int /*<<< orphan*/  kfree (struct iso_resource_event*) ; 
 struct iso_resource_event* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * release_iso_resource ; 
 int /*<<< orphan*/  schedule_iso_resource (struct iso_resource_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_iso_resource(struct client *client,
		struct fw_cdev_allocate_iso_resource *request, int todo)
{
	struct iso_resource_event *e1, *e2;
	struct iso_resource *r;
	int ret;

	if ((request->channels == 0 && request->bandwidth == 0) ||
	    request->bandwidth > BANDWIDTH_AVAILABLE_INITIAL)
		return -EINVAL;

	r  = kmalloc(sizeof(*r), GFP_KERNEL);
	e1 = kmalloc(sizeof(*e1), GFP_KERNEL);
	e2 = kmalloc(sizeof(*e2), GFP_KERNEL);
	if (r == NULL || e1 == NULL || e2 == NULL) {
		ret = -ENOMEM;
		goto fail;
	}

	INIT_DELAYED_WORK(&r->work, iso_resource_work);
	r->client	= client;
	r->todo		= todo;
	r->generation	= -1;
	r->channels	= request->channels;
	r->bandwidth	= request->bandwidth;
	r->e_alloc	= e1;
	r->e_dealloc	= e2;

	e1->iso_resource.closure = request->closure;
	e1->iso_resource.type    = FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED;
	e2->iso_resource.closure = request->closure;
	e2->iso_resource.type    = FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED;

	if (todo == ISO_RES_ALLOC) {
		r->resource.release = release_iso_resource;
		ret = add_client_resource(client, &r->resource, GFP_KERNEL);
		if (ret < 0)
			goto fail;
	} else {
		r->resource.release = NULL;
		r->resource.handle = -1;
		schedule_iso_resource(r, 0);
	}
	request->handle = r->resource.handle;

	return 0;
 fail:
	kfree(r);
	kfree(e1);
	kfree(e2);

	return ret;
}