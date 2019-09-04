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
struct platform_device {int dummy; } ;
struct dss_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int sdi_init_port(struct dss_device *dss,
				struct platform_device *pdev,
				struct device_node *port)
{
	return 0;
}