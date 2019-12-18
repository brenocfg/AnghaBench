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
struct tb_xdomain {int /*<<< orphan*/  properties; } ;
struct tb_service {int /*<<< orphan*/  key; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_PROPERTY_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  tb_property_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tb_service* tb_to_service (struct device*) ; 

__attribute__((used)) static int remove_missing_service(struct device *dev, void *data)
{
	struct tb_xdomain *xd = data;
	struct tb_service *svc;

	svc = tb_to_service(dev);
	if (!svc)
		return 0;

	if (!tb_property_find(xd->properties, svc->key,
			      TB_PROPERTY_TYPE_DIRECTORY))
		device_unregister(dev);

	return 0;
}