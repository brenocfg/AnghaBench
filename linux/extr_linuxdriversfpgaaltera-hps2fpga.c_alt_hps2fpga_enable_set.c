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
struct fpga_bridge {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int _alt_hps2fpga_enable_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alt_hps2fpga_enable_set(struct fpga_bridge *bridge, bool enable)
{
	return _alt_hps2fpga_enable_set(bridge->priv, enable);
}