#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bnxt {TYPE_1__* irq_tbl; TYPE_2__* dev; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_inta ; 
 scalar_t__ netdev_get_num_tc (TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_reset_tc (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int const,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_setup_inta(struct bnxt *bp)
{
	const int len = sizeof(bp->irq_tbl[0].name);

	if (netdev_get_num_tc(bp->dev))
		netdev_reset_tc(bp->dev);

	snprintf(bp->irq_tbl[0].name, len, "%s-%s-%d", bp->dev->name, "TxRx",
		 0);
	bp->irq_tbl[0].handler = bnxt_inta;
}