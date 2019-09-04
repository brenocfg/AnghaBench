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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CR_I2C1 ; 
 scalar_t__ CR_I2C2 ; 

__attribute__((used)) static inline u32 i2c_target(u32 target)
{
	return target ? CR_I2C2 : CR_I2C1;
}