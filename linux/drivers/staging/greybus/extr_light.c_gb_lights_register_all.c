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
struct gb_lights {int lights_count; int /*<<< orphan*/  lights_lock; int /*<<< orphan*/ * lights; struct gb_connection* connection; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gb_lights_light_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_lights_register_all(struct gb_lights *glights)
{
	struct gb_connection *connection = glights->connection;
	int ret = 0;
	int i;

	mutex_lock(&glights->lights_lock);
	for (i = 0; i < glights->lights_count; i++) {
		ret = gb_lights_light_register(&glights->lights[i]);
		if (ret < 0) {
			dev_err(&connection->bundle->dev,
				"Fail to enable lights device\n");
			break;
		}
	}

	mutex_unlock(&glights->lights_lock);
	return ret;
}