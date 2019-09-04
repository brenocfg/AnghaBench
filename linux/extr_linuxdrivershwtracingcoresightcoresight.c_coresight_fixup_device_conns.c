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
struct coresight_device {int nr_outport; int orphan; struct coresight_connection* conns; } ;
struct coresight_connection {int /*<<< orphan*/ * child_dev; scalar_t__ child_name; } ;

/* Variables and functions */
 struct device* bus_find_device_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  coresight_bustype ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/ * to_coresight_device (struct device*) ; 

__attribute__((used)) static void coresight_fixup_device_conns(struct coresight_device *csdev)
{
	int i;

	for (i = 0; i < csdev->nr_outport; i++) {
		struct coresight_connection *conn = &csdev->conns[i];
		struct device *dev = NULL;

		if (conn->child_name)
			dev = bus_find_device_by_name(&coresight_bustype, NULL,
						      conn->child_name);
		if (dev) {
			conn->child_dev = to_coresight_device(dev);
			/* and put reference from 'bus_find_device()' */
			put_device(dev);
		} else {
			csdev->orphan = true;
			conn->child_dev = NULL;
		}
	}
}