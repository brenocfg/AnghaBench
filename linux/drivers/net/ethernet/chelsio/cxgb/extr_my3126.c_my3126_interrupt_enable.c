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
struct cphy {int /*<<< orphan*/  elmer_gpo; int /*<<< orphan*/  adapter; int /*<<< orphan*/  phy_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPO ; 
 int HZ ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int my3126_interrupt_enable(struct cphy *cphy)
{
	schedule_delayed_work(&cphy->phy_update, HZ/30);
	t1_tpi_read(cphy->adapter, A_ELMER0_GPO, &cphy->elmer_gpo);
	return 0;
}