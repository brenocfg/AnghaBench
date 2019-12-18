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
struct cdns3_device {int /*<<< orphan*/ ** eps; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CDNS3_ENDPOINTS_MAX_COUNT ; 
 int /*<<< orphan*/  cdns3_free_trb_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdns3_free_all_eps(struct cdns3_device *priv_dev)
{
	int i;

	/* ep0 OUT point to ep0 IN. */
	priv_dev->eps[16] = NULL;

	for (i = 0; i < CDNS3_ENDPOINTS_MAX_COUNT; i++)
		if (priv_dev->eps[i]) {
			cdns3_free_trb_pool(priv_dev->eps[i]);
			devm_kfree(priv_dev->dev, priv_dev->eps[i]);
		}
}