#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ni_route_tables {struct ni_device_routes const* valid_routes; int /*<<< orphan*/  const* route_values; } ;
struct ni_device_routes {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** register_values; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__** ni_all_route_values ; 
 struct ni_device_routes** ni_device_routes_list ; 
 int /*<<< orphan*/  strnlen (char const*,int) ; 

__attribute__((used)) static int ni_find_device_routes(const char *device_family,
				 const char *board_name,
				 struct ni_route_tables *tables)
{
	const struct ni_device_routes *dr = NULL;
	const u8 *rv = NULL;
	int i;

	/* First, find the register_values table for this device family */
	for (i = 0; ni_all_route_values[i]; ++i) {
		if (memcmp(ni_all_route_values[i]->family, device_family,
			   strnlen(device_family, 30)) == 0) {
			rv = &ni_all_route_values[i]->register_values[0][0];
			break;
		}
	}

	if (!rv)
		return -ENODATA;

	/* Second, find the set of routes valid for this device. */
	for (i = 0; ni_device_routes_list[i]; ++i) {
		if (memcmp(ni_device_routes_list[i]->device, board_name,
			   strnlen(board_name, 30)) == 0) {
			dr = ni_device_routes_list[i];
			break;
		}
	}

	if (!dr)
		return -ENODATA;

	tables->route_values = rv;
	tables->valid_routes = dr;

	return 0;
}