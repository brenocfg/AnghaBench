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
struct ksz_device {int dummy; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SW_LUE_CTRL_1 ; 
 int /*<<< orphan*/  SW_FAST_AGING ; 
 int /*<<< orphan*/  ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz_port_fast_age(struct dsa_switch *ds, int port)
{
	struct ksz_device *dev = ds->priv;
	u8 data8;

	ksz_read8(dev, REG_SW_LUE_CTRL_1, &data8);
	data8 |= SW_FAST_AGING;
	ksz_write8(dev, REG_SW_LUE_CTRL_1, data8);

	data8 &= ~SW_FAST_AGING;
	ksz_write8(dev, REG_SW_LUE_CTRL_1, data8);
}