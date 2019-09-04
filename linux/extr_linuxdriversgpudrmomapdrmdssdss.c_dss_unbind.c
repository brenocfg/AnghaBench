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
 int /*<<< orphan*/  component_unbind_all (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omapdss_set_dss (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dss_unbind(struct device *dev)
{
	omapdss_set_dss(NULL);

	component_unbind_all(dev, NULL);
}