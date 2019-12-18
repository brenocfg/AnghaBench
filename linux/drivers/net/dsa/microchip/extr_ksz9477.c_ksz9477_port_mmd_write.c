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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMD_SETUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_MMD_OP_DATA_NO_INCR ; 
 int /*<<< orphan*/  PORT_MMD_OP_INDEX ; 
 int /*<<< orphan*/  REG_PORT_PHY_MMD_INDEX_DATA ; 
 int /*<<< orphan*/  REG_PORT_PHY_MMD_SETUP ; 
 int /*<<< orphan*/  ksz_pwrite16 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz9477_port_mmd_write(struct ksz_device *dev, int port,
				   u8 dev_addr, u16 reg_addr, u16 val)
{
	ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_SETUP,
		     MMD_SETUP(PORT_MMD_OP_INDEX, dev_addr));
	ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_INDEX_DATA, reg_addr);
	ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_SETUP,
		     MMD_SETUP(PORT_MMD_OP_DATA_NO_INCR, dev_addr));
	ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_INDEX_DATA, val);
}