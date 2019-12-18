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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  version; } ;
struct cpsw_common {int /*<<< orphan*/  ale; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_ale_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 

void cpsw_get_regs(struct net_device *ndev, struct ethtool_regs *regs, void *p)
{
	u32 *reg = p;
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);

	/* update CPSW IP version */
	regs->version = cpsw->version;

	cpsw_ale_dump(cpsw->ale, reg);
}