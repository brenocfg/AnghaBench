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
struct ksz_device {int dummy; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ksz_pwrite16 (struct ksz_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksz_phy_write16(struct dsa_switch *ds, int addr, int reg, u16 val)
{
	struct ksz_device *dev = ds->priv;

	ksz_pwrite16(dev, addr, 0x100 + (reg << 1), val);

	return 0;
}