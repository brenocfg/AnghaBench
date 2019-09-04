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
typedef  int /*<<< orphan*/  u8 ;
struct dpot_data {int feat; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int F_SPI ; 
 int /*<<< orphan*/  dpot_read_i2c (struct dpot_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpot_read_spi (struct dpot_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 dpot_read(struct dpot_data *dpot, u8 reg)
{
	if (dpot->feat & F_SPI)
		return dpot_read_spi(dpot, reg);
	else
		return dpot_read_i2c(dpot, reg);
}