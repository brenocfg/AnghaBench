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
struct gb_interface {int /*<<< orphan*/  hd; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int GB_CONNECTION_FLAG_CONTROL ; 
 int GB_CONNECTION_FLAG_HIGH_PRIO ; 
 struct gb_connection* _gb_connection_create (int /*<<< orphan*/ ,int,struct gb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

struct gb_connection *
gb_connection_create_control(struct gb_interface *intf)
{
	return _gb_connection_create(intf->hd, -1, intf, NULL, 0, NULL,
				     GB_CONNECTION_FLAG_CONTROL |
				     GB_CONNECTION_FLAG_HIGH_PRIO);
}