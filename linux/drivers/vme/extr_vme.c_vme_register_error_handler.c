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
typedef  int /*<<< orphan*/  u32 ;
struct vme_error_handler {unsigned long long start; unsigned long long end; int /*<<< orphan*/  list; scalar_t__ first_error; scalar_t__ num_errors; int /*<<< orphan*/  aspace; } ;
struct vme_bridge {int /*<<< orphan*/  vme_error_handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct vme_error_handler* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct vme_error_handler *vme_register_error_handler(
	struct vme_bridge *bridge, u32 aspace,
	unsigned long long address, size_t len)
{
	struct vme_error_handler *handler;

	handler = kmalloc(sizeof(*handler), GFP_ATOMIC);
	if (!handler)
		return NULL;

	handler->aspace = aspace;
	handler->start = address;
	handler->end = address + len;
	handler->num_errors = 0;
	handler->first_error = 0;
	list_add_tail(&handler->list, &bridge->vme_error_handlers);

	return handler;
}