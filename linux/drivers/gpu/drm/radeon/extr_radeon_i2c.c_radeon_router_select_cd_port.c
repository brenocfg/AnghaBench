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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/  cd_mux_state; int /*<<< orphan*/  cd_mux_control_pin; int /*<<< orphan*/  cd_valid; } ;
struct radeon_connector {TYPE_1__ router; int /*<<< orphan*/  router_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_i2c_get_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_i2c_put_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void radeon_router_select_cd_port(struct radeon_connector *radeon_connector)
{
	u8 val;

	if (!radeon_connector->router.cd_valid)
		return;

	if (!radeon_connector->router_bus)
		return;

	radeon_i2c_get_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x3, &val);
	val &= ~radeon_connector->router.cd_mux_control_pin;
	radeon_i2c_put_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x3, val);
	radeon_i2c_get_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x1, &val);
	val &= ~radeon_connector->router.cd_mux_control_pin;
	val |= radeon_connector->router.cd_mux_state;
	radeon_i2c_put_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x1, val);
}