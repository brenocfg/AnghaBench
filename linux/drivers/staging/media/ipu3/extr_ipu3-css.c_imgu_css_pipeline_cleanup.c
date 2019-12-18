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
struct imgu_device {int dummy; } ;
struct imgu_css {TYPE_2__* pipes; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * binary_params_p; int /*<<< orphan*/  obgrid; int /*<<< orphan*/  gdc; int /*<<< orphan*/  acc; int /*<<< orphan*/  parameter_set_info; } ;
struct TYPE_4__ {TYPE_1__ pool; } ;

/* Variables and functions */
 unsigned int IMGU_ABI_NUM_MEMORIES ; 
 struct imgu_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_css_pool_cleanup (struct imgu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imgu_css_pipeline_cleanup(struct imgu_css *css, unsigned int pipe)
{
	struct imgu_device *imgu = dev_get_drvdata(css->dev);
	unsigned int i;

	imgu_css_pool_cleanup(imgu,
			      &css->pipes[pipe].pool.parameter_set_info);
	imgu_css_pool_cleanup(imgu, &css->pipes[pipe].pool.acc);
	imgu_css_pool_cleanup(imgu, &css->pipes[pipe].pool.gdc);
	imgu_css_pool_cleanup(imgu, &css->pipes[pipe].pool.obgrid);

	for (i = 0; i < IMGU_ABI_NUM_MEMORIES; i++)
		imgu_css_pool_cleanup(imgu,
				      &css->pipes[pipe].pool.binary_params_p[i]);
}