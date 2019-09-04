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
struct tegra_hsp_doorbell {int dummy; } ;
struct tegra_hsp {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct tegra_hsp_doorbell* __tegra_hsp_doorbell_get (struct tegra_hsp*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct tegra_hsp_doorbell *
tegra_hsp_doorbell_get(struct tegra_hsp *hsp, unsigned int master)
{
	struct tegra_hsp_doorbell *db;
	unsigned long flags;

	spin_lock_irqsave(&hsp->lock, flags);
	db = __tegra_hsp_doorbell_get(hsp, master);
	spin_unlock_irqrestore(&hsp->lock, flags);

	return db;
}