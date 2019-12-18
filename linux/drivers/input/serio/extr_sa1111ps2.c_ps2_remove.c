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
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct sa1111_dev {TYPE_1__ res; } ;
struct ps2if {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ps2if*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 struct ps2if* sa1111_get_drvdata (struct sa1111_dev*) ; 
 int /*<<< orphan*/  sa1111_set_drvdata (struct sa1111_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps2_remove(struct sa1111_dev *dev)
{
	struct ps2if *ps2if = sa1111_get_drvdata(dev);

	serio_unregister_port(ps2if->io);
	release_mem_region(dev->res.start, resource_size(&dev->res));
	sa1111_set_drvdata(dev, NULL);

	kfree(ps2if);

	return 0;
}