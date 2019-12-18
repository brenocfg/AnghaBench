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
struct sti_vtg {int dummy; } ;
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 

struct sti_vtg *of_vtg_find(struct device_node *np)
{
	struct platform_device *pdev;

	pdev = of_find_device_by_node(np);
	if (!pdev)
		return NULL;

	return (struct sti_vtg *)platform_get_drvdata(pdev);
}