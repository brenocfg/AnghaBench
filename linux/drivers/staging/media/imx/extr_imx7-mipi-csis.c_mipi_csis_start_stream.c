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
struct csi_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipi_csis_enable_interrupts (struct csi_state*,int) ; 
 int /*<<< orphan*/  mipi_csis_set_params (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_sw_reset (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_system_enable (struct csi_state*,int) ; 

__attribute__((used)) static void mipi_csis_start_stream(struct csi_state *state)
{
	mipi_csis_sw_reset(state);
	mipi_csis_set_params(state);
	mipi_csis_system_enable(state, true);
	mipi_csis_enable_interrupts(state, true);
}