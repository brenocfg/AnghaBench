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
struct emac_board_info {scalar_t__ membase; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ EMAC_CTL_REG ; 
 int /*<<< orphan*/  EMAC_CTL_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void emac_reset(struct emac_board_info *db)
{
	dev_dbg(db->dev, "resetting device\n");

	/* RESET device */
	writel(0, db->membase + EMAC_CTL_REG);
	udelay(200);
	writel(EMAC_CTL_RESET, db->membase + EMAC_CTL_REG);
	udelay(200);
}