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
struct platform_device {int dummy; } ;
struct TYPE_2__ {unsigned int dec_capability; } ;
struct mtk_vpu {TYPE_1__ run; } ;

/* Variables and functions */
 struct mtk_vpu* platform_get_drvdata (struct platform_device*) ; 

unsigned int vpu_get_vdec_hw_capa(struct platform_device *pdev)
{
	struct mtk_vpu *vpu = platform_get_drvdata(pdev);

	return vpu->run.dec_capability;
}