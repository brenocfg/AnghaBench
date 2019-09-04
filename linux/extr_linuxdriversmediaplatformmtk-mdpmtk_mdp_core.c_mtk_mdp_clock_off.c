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
struct mtk_mdp_dev {int /*<<< orphan*/ * comp; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_mdp_comp_clock_off (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_mdp_clock_off(struct mtk_mdp_dev *mdp)
{
	struct device *dev = &mdp->pdev->dev;
	int i;

	for (i = 0; i < ARRAY_SIZE(mdp->comp); i++)
		mtk_mdp_comp_clock_off(dev, mdp->comp[i]);
}