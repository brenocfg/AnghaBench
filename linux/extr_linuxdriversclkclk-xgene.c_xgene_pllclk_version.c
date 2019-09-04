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
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static int xgene_pllclk_version(struct device_node *np)
{
	if (of_device_is_compatible(np, "apm,xgene-socpll-clock"))
		return 1;
	if (of_device_is_compatible(np, "apm,xgene-pcppll-clock"))
		return 1;
	return 2;
}