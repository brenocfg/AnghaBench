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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int component_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdp5_ops ; 
 int mdp5_setup_interconnect (struct platform_device*) ; 

__attribute__((used)) static int mdp5_dev_probe(struct platform_device *pdev)
{
	int ret;

	DBG("");

	ret = mdp5_setup_interconnect(pdev);
	if (ret)
		return ret;

	return component_add(&pdev->dev, &mdp5_ops);
}