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
struct ipu_pre {scalar_t__ buffer_virt; int /*<<< orphan*/  iram; int /*<<< orphan*/  clk_axi; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int IPU_PRE_MAX_WIDTH ; 
 int IPU_PRE_NUM_SCANLINES ; 
 int /*<<< orphan*/  available_pres ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  ipu_pre_list_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ipu_pre* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ipu_pre_remove(struct platform_device *pdev)
{
	struct ipu_pre *pre = platform_get_drvdata(pdev);

	mutex_lock(&ipu_pre_list_mutex);
	list_del(&pre->list);
	available_pres--;
	mutex_unlock(&ipu_pre_list_mutex);

	clk_disable_unprepare(pre->clk_axi);

	if (pre->buffer_virt)
		gen_pool_free(pre->iram, (unsigned long)pre->buffer_virt,
			      IPU_PRE_MAX_WIDTH * IPU_PRE_NUM_SCANLINES * 4);
	return 0;
}