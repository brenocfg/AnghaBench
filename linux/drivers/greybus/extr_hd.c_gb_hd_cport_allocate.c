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
struct ida {int dummy; } ;
struct gb_host_device {int num_cports; int /*<<< orphan*/  dev; TYPE_1__* driver; struct ida cport_id_map; } ;
struct TYPE_2__ {int (* cport_allocate ) (struct gb_host_device*,int,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int ida_simple_get (struct ida*,int,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct gb_host_device*,int,unsigned long) ; 

int gb_hd_cport_allocate(struct gb_host_device *hd, int cport_id,
			 unsigned long flags)
{
	struct ida *id_map = &hd->cport_id_map;
	int ida_start, ida_end;

	if (hd->driver->cport_allocate)
		return hd->driver->cport_allocate(hd, cport_id, flags);

	if (cport_id < 0) {
		ida_start = 0;
		ida_end = hd->num_cports;
	} else if (cport_id < hd->num_cports) {
		ida_start = cport_id;
		ida_end = cport_id + 1;
	} else {
		dev_err(&hd->dev, "cport %d not available\n", cport_id);
		return -EINVAL;
	}

	return ida_simple_get(id_map, ida_start, ida_end, GFP_KERNEL);
}