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
struct camif_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ ** clock; } ;

/* Variables and functions */
 int CLK_MAX_NUM ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  camif_clk_put (struct camif_dev*) ; 
 int /*<<< orphan*/ * camif_clocks ; 
 int /*<<< orphan*/ * clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int camif_clk_get(struct camif_dev *camif)
{
	int ret, i;

	for (i = 1; i < CLK_MAX_NUM; i++)
		camif->clock[i] = ERR_PTR(-EINVAL);

	for (i = 0; i < CLK_MAX_NUM; i++) {
		camif->clock[i] = clk_get(camif->dev, camif_clocks[i]);
		if (IS_ERR(camif->clock[i])) {
			ret = PTR_ERR(camif->clock[i]);
			goto err;
		}
		ret = clk_prepare(camif->clock[i]);
		if (ret < 0) {
			clk_put(camif->clock[i]);
			camif->clock[i] = NULL;
			goto err;
		}
	}
	return 0;
err:
	camif_clk_put(camif);
	dev_err(camif->dev, "failed to get clock: %s\n",
		camif_clocks[i]);
	return ret;
}