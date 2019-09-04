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
typedef  size_t vci_t ;
struct TYPE_2__ {int /*<<< orphan*/  endptr; int /*<<< orphan*/  (* unqueue ) (struct lanai_dev*,struct lanai_vcc*,int /*<<< orphan*/ ) ;} ;
struct lanai_vcc {TYPE_1__ tx; } ;
struct lanai_dev {struct lanai_vcc** vccs; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct lanai_dev*,struct lanai_vcc*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcc_is_backlogged (struct lanai_vcc*) ; 

__attribute__((used)) static void iter_transmit(struct lanai_dev *lanai, vci_t vci)
{
	struct lanai_vcc *lvcc = lanai->vccs[vci];
	if (vcc_is_backlogged(lvcc))
		lvcc->tx.unqueue(lanai, lvcc, lvcc->tx.endptr);
}