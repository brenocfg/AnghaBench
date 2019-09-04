#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  stv06xx_write_bridge (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stv06xx_write_sensor_bytes (struct sd*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* stv_bridge_init ; 
 TYPE_1__* vv6410_sensor_init ; 

__attribute__((used)) static int vv6410_init(struct sd *sd)
{
	int err = 0, i;

	for (i = 0; i < ARRAY_SIZE(stv_bridge_init); i++)
		stv06xx_write_bridge(sd, stv_bridge_init[i].addr, stv_bridge_init[i].data);

	err = stv06xx_write_sensor_bytes(sd, (u8 *) vv6410_sensor_init,
					 ARRAY_SIZE(vv6410_sensor_init));
	return (err < 0) ? err : 0;
}