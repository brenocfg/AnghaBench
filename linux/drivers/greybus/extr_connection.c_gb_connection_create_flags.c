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
typedef  int /*<<< orphan*/  u16 ;
struct gb_interface {int /*<<< orphan*/  hd; } ;
struct gb_connection {int dummy; } ;
struct gb_bundle {struct gb_interface* intf; } ;
typedef  int /*<<< orphan*/  gb_request_handler_t ;

/* Variables and functions */
 unsigned long GB_CONNECTION_FLAG_CORE_MASK ; 
 scalar_t__ WARN_ON_ONCE (unsigned long) ; 
 struct gb_connection* _gb_connection_create (int /*<<< orphan*/ ,int,struct gb_interface*,struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

struct gb_connection *
gb_connection_create_flags(struct gb_bundle *bundle, u16 cport_id,
			   gb_request_handler_t handler,
			   unsigned long flags)
{
	struct gb_interface *intf = bundle->intf;

	if (WARN_ON_ONCE(flags & GB_CONNECTION_FLAG_CORE_MASK))
		flags &= ~GB_CONNECTION_FLAG_CORE_MASK;

	return _gb_connection_create(intf->hd, -1, intf, bundle, cport_id,
				     handler, flags);
}