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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_i2c_bus_rec {int /*<<< orphan*/  y_clk_mask; int /*<<< orphan*/  y_clk_reg; } ;
struct amdgpu_i2c_chan {struct amdgpu_i2c_bus_rec rec; TYPE_1__* dev; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_i2c_get_clock(void *i2c_priv)
{
	struct amdgpu_i2c_chan *i2c = i2c_priv;
	struct amdgpu_device *adev = i2c->dev->dev_private;
	struct amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uint32_t val;

	/* read the value off the pin */
	val = RREG32(rec->y_clk_reg);
	val &= rec->y_clk_mask;

	return (val != 0);
}