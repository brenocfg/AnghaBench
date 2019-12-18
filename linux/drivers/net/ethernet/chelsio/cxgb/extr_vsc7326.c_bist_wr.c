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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RAM_BIST_CMD ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bist_wr(adapter_t *adapter, int moduleid, int address, int value)
{
	int data = 0;
	u32 result = 0;

	if ((address != 0x0) &&
	    (address != 0x1) &&
	    (address != 0x2) &&
	    (address != 0xd) &&
	    (address != 0xe))
			pr_err("No bist address: 0x%x\n", address);

	if (value > 255)
		pr_err("Suspicious write out of range value: 0x%x\n", value);

	data = ((0x01 << 24) | ((address & 0xff) << 16) | (value << 8) |
		((moduleid & 0xff) << 0));
	vsc_write(adapter, REG_RAM_BIST_CMD, data);

	udelay(5);

	vsc_read(adapter, REG_RAM_BIST_CMD, &result);
	if ((result & (1 << 27)) != 0x0)
		pr_err("Still in bist write: 0x%x\n", result);
	else if ((result & (1 << 26)) != 0x0)
		pr_err("bist write error: 0x%x\n", result);

	return 0;
}