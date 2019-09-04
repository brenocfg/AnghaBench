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
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct mipi_dsi_device* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mipi_dsi_device *
of_mipi_dsi_device_add(struct mipi_dsi_host *host, struct device_node *node)
{
	return ERR_PTR(-ENODEV);
}