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
struct device {int dummy; } ;
struct coresight_device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coresight_bustype ; 
 int /*<<< orphan*/  coresight_enabled_sink ; 
 struct coresight_device* to_coresight_device (struct device*) ; 

struct coresight_device *coresight_get_enabled_sink(bool deactivate)
{
	struct device *dev = NULL;

	dev = bus_find_device(&coresight_bustype, NULL, &deactivate,
			      coresight_enabled_sink);

	return dev ? to_coresight_device(dev) : NULL;
}