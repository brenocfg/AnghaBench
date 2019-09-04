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
typedef  void iio_trigger ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int devm_iio_trigger_match(struct device *dev, void *res, void *data)
{
	struct iio_trigger **r = res;

	if (!r || !*r) {
		WARN_ON(!r || !*r);
		return 0;
	}

	return *r == data;
}