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
struct st_rproc {int /*<<< orphan*/ * mbox_chan; int /*<<< orphan*/  clk; } ;
struct rproc {struct st_rproc* priv; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int MBOX_MAX ; 
 int ST_RPROC_MAX_VRING ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 struct rproc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rproc_del (struct rproc*) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 

__attribute__((used)) static int st_rproc_remove(struct platform_device *pdev)
{
	struct rproc *rproc = platform_get_drvdata(pdev);
	struct st_rproc *ddata = rproc->priv;
	int i;

	rproc_del(rproc);

	clk_disable_unprepare(ddata->clk);

	for (i = 0; i < ST_RPROC_MAX_VRING * MBOX_MAX; i++)
		mbox_free_channel(ddata->mbox_chan[i]);

	rproc_free(rproc);

	return 0;
}