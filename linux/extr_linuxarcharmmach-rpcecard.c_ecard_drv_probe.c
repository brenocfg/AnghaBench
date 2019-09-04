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
struct expansion_card {int claimed; } ;
struct ecard_id {int dummy; } ;
struct ecard_driver {int (* probe ) (struct expansion_card*,struct ecard_id const*) ;int /*<<< orphan*/  id_table; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct expansion_card* ECARD_DEV (struct device*) ; 
 struct ecard_driver* ECARD_DRV (int /*<<< orphan*/ ) ; 
 struct ecard_id* ecard_match_device (int /*<<< orphan*/ ,struct expansion_card*) ; 
 int stub1 (struct expansion_card*,struct ecard_id const*) ; 

__attribute__((used)) static int ecard_drv_probe(struct device *dev)
{
	struct expansion_card *ec = ECARD_DEV(dev);
	struct ecard_driver *drv = ECARD_DRV(dev->driver);
	const struct ecard_id *id;
	int ret;

	id = ecard_match_device(drv->id_table, ec);

	ec->claimed = 1;
	ret = drv->probe(ec, id);
	if (ret)
		ec->claimed = 0;
	return ret;
}