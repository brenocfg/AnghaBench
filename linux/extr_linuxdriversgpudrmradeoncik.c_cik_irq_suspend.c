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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cik_irq_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_rlc_stop (struct radeon_device*) ; 

__attribute__((used)) static void cik_irq_suspend(struct radeon_device *rdev)
{
	cik_irq_disable(rdev);
	cik_rlc_stop(rdev);
}