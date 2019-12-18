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
struct mmc_host {int dummy; } ;
struct cb710_slot {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 struct mmc_host* platform_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct mmc_host *cb710_slot_to_mmc(struct cb710_slot *slot)
{
	return platform_get_drvdata(&slot->pdev);
}