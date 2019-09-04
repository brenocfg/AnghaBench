#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct de_private {TYPE_1__* dev; } ;
struct TYPE_2__ {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROMCmd ; 
 int dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void de21040_get_mac_address(struct de_private *de)
{
	unsigned i;

	dw32 (ROMCmd, 0);	/* Reset the pointer with a dummy write. */
	udelay(5);

	for (i = 0; i < 6; i++) {
		int value, boguscnt = 100000;
		do {
			value = dr32(ROMCmd);
			rmb();
		} while (value < 0 && --boguscnt > 0);
		de->dev->dev_addr[i] = value;
		udelay(1);
		if (boguscnt <= 0)
			pr_warn("timeout reading 21040 MAC address byte %u\n",
				i);
	}
}