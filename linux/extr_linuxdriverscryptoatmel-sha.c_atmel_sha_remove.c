#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ has_dma; } ;
struct atmel_sha_dev {int /*<<< orphan*/  iclk; TYPE_1__ caps; int /*<<< orphan*/  done_task; int /*<<< orphan*/  queue_task; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ atmel_sha ; 
 int /*<<< orphan*/  atmel_sha_dma_cleanup (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_unregister_algs (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct atmel_sha_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_sha_remove(struct platform_device *pdev)
{
	struct atmel_sha_dev *sha_dd;

	sha_dd = platform_get_drvdata(pdev);
	if (!sha_dd)
		return -ENODEV;
	spin_lock(&atmel_sha.lock);
	list_del(&sha_dd->list);
	spin_unlock(&atmel_sha.lock);

	atmel_sha_unregister_algs(sha_dd);

	tasklet_kill(&sha_dd->queue_task);
	tasklet_kill(&sha_dd->done_task);

	if (sha_dd->caps.has_dma)
		atmel_sha_dma_cleanup(sha_dd);

	clk_unprepare(sha_dd->iclk);

	return 0;
}