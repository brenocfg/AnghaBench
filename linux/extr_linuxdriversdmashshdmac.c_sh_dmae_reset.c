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
struct sh_dmae_device {int /*<<< orphan*/  shdma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  sh_dmae_ctl_stop (struct sh_dmae_device*) ; 
 int /*<<< orphan*/  sh_dmae_rst (struct sh_dmae_device*) ; 
 int shdma_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sh_dmae_reset(struct sh_dmae_device *shdev)
{
	bool ret;

	/* halt the dma controller */
	sh_dmae_ctl_stop(shdev);

	/* We cannot detect, which channel caused the error, have to reset all */
	ret = shdma_reset(&shdev->shdma_dev);

	sh_dmae_rst(shdev);

	return ret;
}