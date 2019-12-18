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
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_NCR5380_release_resources (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int generic_NCR5380_isa_remove(struct device *pdev,
                                      unsigned int ndev)
{
	generic_NCR5380_release_resources(dev_get_drvdata(pdev));
	dev_set_drvdata(pdev, NULL);
	return 0;
}