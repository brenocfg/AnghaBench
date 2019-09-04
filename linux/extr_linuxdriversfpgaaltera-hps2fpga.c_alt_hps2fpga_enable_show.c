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
struct fpga_bridge {struct altera_hps2fpga_data* priv; } ;
struct altera_hps2fpga_data {int /*<<< orphan*/  bridge_reset; } ;

/* Variables and functions */
 int reset_control_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alt_hps2fpga_enable_show(struct fpga_bridge *bridge)
{
	struct altera_hps2fpga_data *priv = bridge->priv;

	return reset_control_status(priv->bridge_reset);
}