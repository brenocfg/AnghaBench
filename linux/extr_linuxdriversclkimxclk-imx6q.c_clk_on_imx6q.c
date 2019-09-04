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

/* Variables and functions */
 int of_machine_is_compatible (char*) ; 

__attribute__((used)) static inline int clk_on_imx6q(void)
{
	return of_machine_is_compatible("fsl,imx6q");
}