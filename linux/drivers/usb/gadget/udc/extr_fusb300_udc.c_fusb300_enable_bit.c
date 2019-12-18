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
struct fusb300 {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void fusb300_enable_bit(struct fusb300 *fusb300, u32 offset,
			       u32 value)
{
	u32 reg = ioread32(fusb300->reg + offset);

	reg |= value;
	iowrite32(reg, fusb300->reg + offset);
}