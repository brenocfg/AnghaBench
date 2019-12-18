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
 int /*<<< orphan*/  MIPI_CSIS_INTMSK ; 
 int /*<<< orphan*/  mipi_csis_write (struct csi_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mipi_csis_enable_interrupts(struct csi_state *state, bool on)
{
	mipi_csis_write(state, MIPI_CSIS_INTMSK, on ? 0xffffffff : 0);
}