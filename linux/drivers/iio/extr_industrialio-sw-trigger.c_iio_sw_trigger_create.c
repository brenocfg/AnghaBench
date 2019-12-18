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
struct iio_sw_trigger_type {int /*<<< orphan*/  owner; TYPE_1__* ops; } ;
struct iio_sw_trigger {struct iio_sw_trigger_type* trigger_type; } ;
struct TYPE_2__ {struct iio_sw_trigger* (* probe ) (char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct iio_sw_trigger* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct iio_sw_trigger*) ; 
 struct iio_sw_trigger_type* iio_get_sw_trigger_type (char const*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 struct iio_sw_trigger* stub1 (char const*) ; 

struct iio_sw_trigger *iio_sw_trigger_create(const char *type, const char *name)
{
	struct iio_sw_trigger *t;
	struct iio_sw_trigger_type *tt;

	tt = iio_get_sw_trigger_type(type);
	if (!tt) {
		pr_err("Invalid trigger type: %s\n", type);
		return ERR_PTR(-EINVAL);
	}
	t = tt->ops->probe(name);
	if (IS_ERR(t))
		goto out_module_put;

	t->trigger_type = tt;

	return t;
out_module_put:
	module_put(tt->owner);
	return t;
}