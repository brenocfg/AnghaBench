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
typedef  int u32 ;
struct csi_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_CSIS_DPHYCTRL ; 
 int MIPI_CSIS_DPHYCTRL_HSS_MASK ; 
 int mipi_csis_read (struct csi_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_write (struct csi_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mipi_csis_set_hsync_settle(struct csi_state *state, int hs_settle)
{
	u32 val = mipi_csis_read(state, MIPI_CSIS_DPHYCTRL);

	val = ((val & ~MIPI_CSIS_DPHYCTRL_HSS_MASK) | (hs_settle << 24));

	mipi_csis_write(state, MIPI_CSIS_DPHYCTRL, val);
}