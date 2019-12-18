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
struct ni_route_tables {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ni_route_tables*,int /*<<< orphan*/ ,int) ; 
 int ni_find_device_routes (char const*,char const*,struct ni_route_tables*) ; 

int ni_assign_device_routes(const char *device_family,
			    const char *board_name,
			    struct ni_route_tables *tables)
{
	memset(tables, 0, sizeof(struct ni_route_tables));
	return ni_find_device_routes(device_family, board_name, tables);
}