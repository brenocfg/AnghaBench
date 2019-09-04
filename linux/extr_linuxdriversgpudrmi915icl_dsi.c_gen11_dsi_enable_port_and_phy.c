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
struct intel_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen11_dsi_power_up_lanes (struct intel_encoder*) ; 

__attribute__((used)) static void gen11_dsi_enable_port_and_phy(struct intel_encoder *encoder)
{
	/* step 4a: power up all lanes of the DDI used by DSI */
	gen11_dsi_power_up_lanes(encoder);
}