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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mtk_vcodec_dev {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 

void mtk_vcodec_release_dec_pm(struct mtk_vcodec_dev *dev)
{
	pm_runtime_disable(dev->pm.dev);
}