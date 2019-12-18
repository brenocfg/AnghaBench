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
 int /*<<< orphan*/  CONFIG_GCR ; 
 int gx1_read_conf_reg (int /*<<< orphan*/ ) ; 

unsigned gx1_gx_base(void)
{
	return (gx1_read_conf_reg(CONFIG_GCR) & 0x03) << 30;
}