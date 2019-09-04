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
typedef  int /*<<< orphan*/  u16 ;
struct bgmac {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int bgmac_read (struct bgmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool bgmac_wait_value(struct bgmac *bgmac, u16 reg, u32 mask,
			     u32 value, int timeout)
{
	u32 val;
	int i;

	for (i = 0; i < timeout / 10; i++) {
		val = bgmac_read(bgmac, reg);
		if ((val & mask) == value)
			return true;
		udelay(10);
	}
	dev_err(bgmac->dev, "Timeout waiting for reg 0x%X\n", reg);
	return false;
}