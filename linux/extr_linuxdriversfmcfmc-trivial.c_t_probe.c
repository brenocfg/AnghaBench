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
struct fmc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  fmc_gpio_config (struct fmc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmc_irq_free (struct fmc_device*) ; 
 int fmc_irq_request (struct fmc_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fmc_reprogram (struct fmc_device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int fmc_validate (struct fmc_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t_drv ; 
 int /*<<< orphan*/  t_gpio ; 
 int /*<<< orphan*/  t_handler ; 

__attribute__((used)) static int t_probe(struct fmc_device *fmc)
{
	int ret;
	int index = 0;

	index = fmc_validate(fmc, &t_drv);
	if (index < 0)
		return -EINVAL; /* not our device: invalid */

	ret = fmc_irq_request(fmc, t_handler, "fmc-trivial", IRQF_SHARED);
	if (ret < 0)
		return ret;
	/* ignore error code of call below, we really don't care */
	fmc_gpio_config(fmc, t_gpio, ARRAY_SIZE(t_gpio));

	ret = fmc_reprogram(fmc, &t_drv, "", 0);
	if (ret == -EPERM) /* programming not supported */
		ret = 0;
	if (ret < 0)
		fmc_irq_free(fmc);

	/* FIXME: reprogram LM32 too */
	return ret;
}