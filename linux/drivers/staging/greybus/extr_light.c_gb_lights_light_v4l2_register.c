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
struct gb_light {int dummy; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gb_connection* get_conn_from_light (struct gb_light*) ; 

__attribute__((used)) static int gb_lights_light_v4l2_register(struct gb_light *light)
{
	struct gb_connection *connection = get_conn_from_light(light);

	dev_err(&connection->bundle->dev, "no support for v4l2 subdevices\n");
	return 0;
}