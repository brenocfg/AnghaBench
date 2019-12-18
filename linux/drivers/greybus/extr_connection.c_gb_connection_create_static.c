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
struct gb_host_device {int dummy; } ;
struct gb_connection {int dummy; } ;
typedef  int /*<<< orphan*/  gb_request_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  GB_CONNECTION_FLAG_HIGH_PRIO ; 
 struct gb_connection* _gb_connection_create (struct gb_host_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct gb_connection *
gb_connection_create_static(struct gb_host_device *hd, u16 hd_cport_id,
			    gb_request_handler_t handler)
{
	return _gb_connection_create(hd, hd_cport_id, NULL, NULL, 0, handler,
				     GB_CONNECTION_FLAG_HIGH_PRIO);
}