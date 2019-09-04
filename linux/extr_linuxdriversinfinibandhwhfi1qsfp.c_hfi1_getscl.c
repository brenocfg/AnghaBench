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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_i2c_bus {int /*<<< orphan*/  controlling_dd; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int QSFP_HFI0_I2CCLK ; 
 int /*<<< orphan*/  hfi1_setscl (void*,int) ; 
 int /*<<< orphan*/  i2c_in_csr (int /*<<< orphan*/ ) ; 
 int read_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hfi1_getscl(void *data)
{
	struct hfi1_i2c_bus *bus = (struct hfi1_i2c_bus *)data;
	u64 reg;
	u32 target_in;

	hfi1_setscl(data, 1);	/* clear OE so we do not pull line down */
	udelay(2);		/* 1us pull up + 250ns hold */

	target_in = i2c_in_csr(bus->num);
	reg = read_csr(bus->controlling_dd, target_in);
	return !!(reg & QSFP_HFI0_I2CCLK);
}