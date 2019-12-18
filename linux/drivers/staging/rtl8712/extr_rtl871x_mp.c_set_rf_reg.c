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
 int bMaskDWord ; 
 int bitshift (int) ; 
 int r8712_rf_reg_read (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_rf_reg_write (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 set_rf_reg(struct _adapter *pAdapter, u8 path, u8 offset, u32 bitmask,
	      u32 value)
{
	u32 org_value, bit_shift, new_value;

	if (bitmask != bMaskDWord) {
		org_value = r8712_rf_reg_read(pAdapter, path, offset);
		bit_shift = bitshift(bitmask);
		new_value = (org_value & (~bitmask)) | (value << bit_shift);
	} else {
		new_value = value;
	}
	return r8712_rf_reg_write(pAdapter, path, offset, new_value);
}