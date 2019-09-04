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
struct soc_camera_host {TYPE_1__ v4l2_dev; struct sh_mobile_ceu_dev* priv; } ;
struct sh_mobile_ceu_dev {scalar_t__ buf_total; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mobile_ceu_soft_reset (struct sh_mobile_ceu_dev*) ; 

__attribute__((used)) static int sh_mobile_ceu_clock_start(struct soc_camera_host *ici)
{
	struct sh_mobile_ceu_dev *pcdev = ici->priv;

	pm_runtime_get_sync(ici->v4l2_dev.dev);

	pcdev->buf_total = 0;

	sh_mobile_ceu_soft_reset(pcdev);

	return 0;
}