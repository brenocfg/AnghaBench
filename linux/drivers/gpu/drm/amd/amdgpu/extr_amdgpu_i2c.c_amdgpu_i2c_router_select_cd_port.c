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
struct amdgpu_connector {TYPE_1__ router; int /*<<< orphan*/  router_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_i2c_get_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_i2c_put_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
amdgpu_i2c_router_select_cd_port(const struct amdgpu_connector *amdgpu_connector)
{
	u8 val;

	if (!amdgpu_connector->router.cd_valid)
		return;

	if (!amdgpu_connector->router_bus)
		return;

	amdgpu_i2c_get_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x3, &val);
	val &= ~amdgpu_connector->router.cd_mux_control_pin;
	amdgpu_i2c_put_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x3, val);
	amdgpu_i2c_get_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x1, &val);
	val &= ~amdgpu_connector->router.cd_mux_control_pin;
	val |= amdgpu_connector->router.cd_mux_state;
	amdgpu_i2c_put_byte(amdgpu_connector->router_bus,
			    amdgpu_connector->router.i2c_addr,
			    0x1, val);
}