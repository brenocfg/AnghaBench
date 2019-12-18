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
struct zorro_driver {int (* probe ) (struct zorro_dev*,struct zorro_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct zorro_device_id {int dummy; } ;
struct zorro_dev {struct zorro_driver* driver; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (struct zorro_dev*,struct zorro_device_id const*) ; 
 struct zorro_dev* to_zorro_dev (struct device*) ; 
 struct zorro_driver* to_zorro_driver (int /*<<< orphan*/ ) ; 
 struct zorro_device_id* zorro_match_device (int /*<<< orphan*/ ,struct zorro_dev*) ; 

__attribute__((used)) static int zorro_device_probe(struct device *dev)
{
	int error = 0;
	struct zorro_driver *drv = to_zorro_driver(dev->driver);
	struct zorro_dev *z = to_zorro_dev(dev);

	if (!z->driver && drv->probe) {
		const struct zorro_device_id *id;

		id = zorro_match_device(drv->id_table, z);
		if (id)
			error = drv->probe(z, id);
		if (error >= 0) {
			z->driver = drv;
			error = 0;
		}
	}
	return error;
}