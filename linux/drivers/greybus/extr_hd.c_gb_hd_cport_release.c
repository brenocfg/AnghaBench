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
typedef  int /*<<< orphan*/  u16 ;
struct gb_host_device {int /*<<< orphan*/  cport_id_map; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cport_release ) (struct gb_host_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gb_host_device*,int /*<<< orphan*/ ) ; 

void gb_hd_cport_release(struct gb_host_device *hd, u16 cport_id)
{
	if (hd->driver->cport_release) {
		hd->driver->cport_release(hd, cport_id);
		return;
	}

	ida_simple_remove(&hd->cport_id_map, cport_id);
}