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
 int /*<<< orphan*/  glk_dsi_disable_mipi_io (struct intel_encoder*) ; 
 int /*<<< orphan*/  glk_dsi_enter_low_power_mode (struct intel_encoder*) ; 

__attribute__((used)) static void glk_dsi_clear_device_ready(struct intel_encoder *encoder)
{
	glk_dsi_enter_low_power_mode(encoder);
	glk_dsi_disable_mipi_io(encoder);
}