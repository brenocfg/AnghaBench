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
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMI_QMAN ; 
 int /*<<< orphan*/  OMI_QMAN_PRIV ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 

void get_ome_index(u32 *omi_index, struct device *dev)
{
	if (of_device_is_compatible(dev->of_node, "fsl,qman-portal"))
		*omi_index = OMI_QMAN;
	if (of_device_is_compatible(dev->of_node, "fsl,qman"))
		*omi_index = OMI_QMAN_PRIV;
}