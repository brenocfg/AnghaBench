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
typedef  int /*<<< orphan*/  rtl8150_t ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int HZ ; 
 int /*<<< orphan*/  get_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  set_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int rtl8150_reset(rtl8150_t * dev)
{
	u8 data = 0x10;
	int i = HZ;

	set_registers(dev, CR, 1, &data);
	do {
		get_registers(dev, CR, 1, &data);
	} while ((data & 0x10) && --i);

	return (i > 0) ? 1 : 0;
}