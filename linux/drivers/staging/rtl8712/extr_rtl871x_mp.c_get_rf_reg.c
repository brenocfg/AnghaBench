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
typedef  int u32 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int bitshift (int) ; 
 int r8712_rf_reg_read (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_rf_reg(struct _adapter *pAdapter, u8 path, u8 offset,
		      u32 bitmask)
{
	u32 org_value, bit_shift;

	org_value = r8712_rf_reg_read(pAdapter, path, offset);
	bit_shift = bitshift(bitmask);
	return (org_value & bitmask) >> bit_shift;
}