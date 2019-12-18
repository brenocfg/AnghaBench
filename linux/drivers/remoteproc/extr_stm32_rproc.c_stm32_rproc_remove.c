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
struct rproc {int /*<<< orphan*/  power; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct rproc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rproc_del (struct rproc*) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 
 int /*<<< orphan*/  rproc_shutdown (struct rproc*) ; 
 int /*<<< orphan*/  stm32_rproc_free_mbox (struct rproc*) ; 

__attribute__((used)) static int stm32_rproc_remove(struct platform_device *pdev)
{
	struct rproc *rproc = platform_get_drvdata(pdev);

	if (atomic_read(&rproc->power) > 0)
		rproc_shutdown(rproc);

	rproc_del(rproc);
	stm32_rproc_free_mbox(rproc);
	rproc_free(rproc);

	return 0;
}