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
struct xvip_composite_device {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct xvip_composite_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  xvip_composite_v4l2_cleanup (struct xvip_composite_device*) ; 
 int /*<<< orphan*/  xvip_graph_cleanup (struct xvip_composite_device*) ; 

__attribute__((used)) static int xvip_composite_remove(struct platform_device *pdev)
{
	struct xvip_composite_device *xdev = platform_get_drvdata(pdev);

	xvip_graph_cleanup(xdev);
	xvip_composite_v4l2_cleanup(xdev);

	return 0;
}