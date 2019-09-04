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
struct pti_device {scalar_t__ base; } ;
struct intel_th_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ REG_PTI_CTL ; 
 struct pti_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_th_trace_disable (struct intel_th_device*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intel_th_pti_deactivate(struct intel_th_device *thdev)
{
	struct pti_device *pti = dev_get_drvdata(&thdev->dev);

	intel_th_trace_disable(thdev);

	iowrite32(0, pti->base + REG_PTI_CTL);
}