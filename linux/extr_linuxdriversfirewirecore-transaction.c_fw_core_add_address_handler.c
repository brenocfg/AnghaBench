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
struct fw_address_region {int start; int end; } ;
struct fw_address_handler {int length; int offset; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  address_handler_list ; 
 int /*<<< orphan*/  address_handler_list_lock ; 
 scalar_t__ is_in_fcp_region (int,int) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fw_address_handler* lookup_overlapping_address_handler (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int fw_core_add_address_handler(struct fw_address_handler *handler,
				const struct fw_address_region *region)
{
	struct fw_address_handler *other;
	int ret = -EBUSY;

	if (region->start & 0xffff000000000003ULL ||
	    region->start >= region->end ||
	    region->end   > 0x0001000000000000ULL ||
	    handler->length & 3 ||
	    handler->length == 0)
		return -EINVAL;

	spin_lock(&address_handler_list_lock);

	handler->offset = region->start;
	while (handler->offset + handler->length <= region->end) {
		if (is_in_fcp_region(handler->offset, handler->length))
			other = NULL;
		else
			other = lookup_overlapping_address_handler
					(&address_handler_list,
					 handler->offset, handler->length);
		if (other != NULL) {
			handler->offset += other->length;
		} else {
			list_add_tail_rcu(&handler->link, &address_handler_list);
			ret = 0;
			break;
		}
	}

	spin_unlock(&address_handler_list_lock);

	return ret;
}