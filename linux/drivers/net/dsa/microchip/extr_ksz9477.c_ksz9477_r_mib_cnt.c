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
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct ksz_port {scalar_t__ freeze; } ;
struct ksz_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * regmap; struct ksz_port* ports; } ;

/* Variables and functions */
 unsigned int MIB_COUNTER_FLUSH_FREEZE ; 
 unsigned int MIB_COUNTER_INDEX_S ; 
 unsigned int MIB_COUNTER_READ ; 
 int /*<<< orphan*/  PORT_CTRL_ADDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_PORT_MIB_CTRL_STAT__4 ; 
 int /*<<< orphan*/  REG_PORT_MIB_DATA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ksz_pread32 (struct ksz_device*,int,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ksz_pwrite32 (struct ksz_device*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 

__attribute__((used)) static void ksz9477_r_mib_cnt(struct ksz_device *dev, int port, u16 addr,
			      u64 *cnt)
{
	struct ksz_port *p = &dev->ports[port];
	unsigned int val;
	u32 data;
	int ret;

	/* retain the flush/freeze bit */
	data = p->freeze ? MIB_COUNTER_FLUSH_FREEZE : 0;
	data |= MIB_COUNTER_READ;
	data |= (addr << MIB_COUNTER_INDEX_S);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4, data);

	ret = regmap_read_poll_timeout(dev->regmap[2],
			PORT_CTRL_ADDR(port, REG_PORT_MIB_CTRL_STAT__4),
			val, !(val & MIB_COUNTER_READ), 10, 1000);
	/* failed to read MIB. get out of loop */
	if (ret) {
		dev_dbg(dev->dev, "Failed to get MIB\n");
		return;
	}

	/* count resets upon read */
	ksz_pread32(dev, port, REG_PORT_MIB_DATA, &data);
	*cnt += data;
}