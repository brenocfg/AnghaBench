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
struct rk_crypto_info {int /*<<< orphan*/  queue_task; int /*<<< orphan*/  done_task; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct rk_crypto_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rk_crypto_unregister () ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk_crypto_remove(struct platform_device *pdev)
{
	struct rk_crypto_info *crypto_tmp = platform_get_drvdata(pdev);

	rk_crypto_unregister();
	tasklet_kill(&crypto_tmp->done_task);
	tasklet_kill(&crypto_tmp->queue_task);
	return 0;
}