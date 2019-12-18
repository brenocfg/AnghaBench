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
typedef  int u8 ;
struct stk1160 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STK1160_POSV_L ; 
 int STK1160_POSV_L_ACSYNC ; 
 int /*<<< orphan*/  stk1160_read_reg (struct stk1160*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int stk1160_has_ac97(struct stk1160 *dev)
{
	u8 value;

	stk1160_read_reg(dev, STK1160_POSV_L, &value);
	return !(value & STK1160_POSV_L_ACSYNC);
}