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
typedef  int u32 ;
struct efm32_i2c_ddata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ROUTE ; 
 int REG_ROUTE_LOCATION__MASK ; 
 int __ffs (int) ; 
 int efm32_i2c_read32 (struct efm32_i2c_ddata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 efm32_i2c_get_configured_location(struct efm32_i2c_ddata *ddata)
{
	u32 reg = efm32_i2c_read32(ddata, REG_ROUTE);

	return (reg & REG_ROUTE_LOCATION__MASK) >>
		__ffs(REG_ROUTE_LOCATION__MASK);
}