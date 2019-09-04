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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fmr2_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fmr2_isa_remove(struct device *pdev, unsigned int ndev)
{
	fmr2_remove(dev_get_drvdata(pdev));

	return 0;
}