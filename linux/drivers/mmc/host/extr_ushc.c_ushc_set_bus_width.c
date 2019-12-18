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
struct ushc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USHC_HOST_CTRL_4BIT ; 
 int ushc_hw_set_host_ctrl (struct ushc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ushc_set_bus_width(struct ushc_data *ushc, int bus_width)
{
	return ushc_hw_set_host_ctrl(ushc, USHC_HOST_CTRL_4BIT,
				     bus_width == 4 ? USHC_HOST_CTRL_4BIT : 0);
}