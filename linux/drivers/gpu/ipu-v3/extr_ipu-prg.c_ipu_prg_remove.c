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
struct platform_device {int dummy; } ;
struct ipu_prg {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_prg_list_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ipu_prg* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ipu_prg_remove(struct platform_device *pdev)
{
	struct ipu_prg *prg = platform_get_drvdata(pdev);

	mutex_lock(&ipu_prg_list_mutex);
	list_del(&prg->list);
	mutex_unlock(&ipu_prg_list_mutex);

	return 0;
}