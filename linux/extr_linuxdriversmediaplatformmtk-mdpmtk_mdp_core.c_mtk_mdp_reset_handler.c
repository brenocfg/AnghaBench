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
struct mtk_mdp_dev {int /*<<< orphan*/  wdt_work; int /*<<< orphan*/  wdt_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_mdp_reset_handler(void *priv)
{
	struct mtk_mdp_dev *mdp = priv;

	queue_work(mdp->wdt_wq, &mdp->wdt_work);
}