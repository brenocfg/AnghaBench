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
typedef  int /*<<< orphan*/  u16 ;
struct mcp23s08 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int mcp_set_mask (struct mcp23s08*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mcp_set_bit(struct mcp23s08 *mcp, unsigned int reg,
		       unsigned int pin, bool enabled)
{
	u16 mask = BIT(pin);
	return mcp_set_mask(mcp, reg, mask, enabled);
}