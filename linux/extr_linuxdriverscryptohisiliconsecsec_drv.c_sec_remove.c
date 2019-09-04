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
struct sec_dev_info {int /*<<< orphan*/ * queues; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int SEC_Q_NUM ; 
 struct sec_dev_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sec_algs_unregister () ; 
 int /*<<< orphan*/  sec_base_exit (struct sec_dev_info*) ; 
 int /*<<< orphan*/  sec_id_free (struct sec_dev_info*) ; 
 int /*<<< orphan*/  sec_queue_irq_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_queue_unconfig (struct sec_dev_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sec_remove(struct platform_device *pdev)
{
	struct sec_dev_info *info = platform_get_drvdata(pdev);
	int i;

	/* Unexpose as soon as possible, reuse during remove is fine */
	sec_id_free(info);

	sec_algs_unregister();

	for (i = 0; i < SEC_Q_NUM; i++) {
		sec_queue_irq_uninit(&info->queues[i]);
		sec_queue_unconfig(info, &info->queues[i]);
	}

	sec_base_exit(info);

	return 0;
}