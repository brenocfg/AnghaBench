#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct mcb_device {TYPE_3__ mem; TYPE_2__ dev; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 struct resource* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  resource_size (TYPE_3__*) ; 

struct resource *mcb_request_mem(struct mcb_device *dev, const char *name)
{
	struct resource *mem;
	u32 size;

	if (!name)
		name = dev->dev.driver->name;

	size = resource_size(&dev->mem);

	mem = request_mem_region(dev->mem.start, size, name);
	if (!mem)
		return ERR_PTR(-EBUSY);

	return mem;
}