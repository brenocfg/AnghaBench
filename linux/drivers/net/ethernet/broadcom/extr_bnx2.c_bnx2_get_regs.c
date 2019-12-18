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
struct net_device {int dummy; } ;
struct ethtool_regs {scalar_t__ version; } ;
struct bnx2 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_RD (struct bnx2*,int) ; 
 int BNX2_REGDUMP_LEN ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *_p)
{
	u32 *p = _p, i, offset;
	u8 *orig_p = _p;
	struct bnx2 *bp = netdev_priv(dev);
	static const u32 reg_boundaries[] = {
		0x0000, 0x0098, 0x0400, 0x045c,
		0x0800, 0x0880, 0x0c00, 0x0c10,
		0x0c30, 0x0d08, 0x1000, 0x101c,
		0x1040, 0x1048, 0x1080, 0x10a4,
		0x1400, 0x1490, 0x1498, 0x14f0,
		0x1500, 0x155c, 0x1580, 0x15dc,
		0x1600, 0x1658, 0x1680, 0x16d8,
		0x1800, 0x1820, 0x1840, 0x1854,
		0x1880, 0x1894, 0x1900, 0x1984,
		0x1c00, 0x1c0c, 0x1c40, 0x1c54,
		0x1c80, 0x1c94, 0x1d00, 0x1d84,
		0x2000, 0x2030, 0x23c0, 0x2400,
		0x2800, 0x2820, 0x2830, 0x2850,
		0x2b40, 0x2c10, 0x2fc0, 0x3058,
		0x3c00, 0x3c94, 0x4000, 0x4010,
		0x4080, 0x4090, 0x43c0, 0x4458,
		0x4c00, 0x4c18, 0x4c40, 0x4c54,
		0x4fc0, 0x5010, 0x53c0, 0x5444,
		0x5c00, 0x5c18, 0x5c80, 0x5c90,
		0x5fc0, 0x6000, 0x6400, 0x6428,
		0x6800, 0x6848, 0x684c, 0x6860,
		0x6888, 0x6910, 0x8000
	};

	regs->version = 0;

	memset(p, 0, BNX2_REGDUMP_LEN);

	if (!netif_running(bp->dev))
		return;

	i = 0;
	offset = reg_boundaries[0];
	p += offset;
	while (offset < BNX2_REGDUMP_LEN) {
		*p++ = BNX2_RD(bp, offset);
		offset += 4;
		if (offset == reg_boundaries[i + 1]) {
			offset = reg_boundaries[i + 2];
			p = (u32 *) (orig_p + offset);
			i += 2;
		}
	}
}