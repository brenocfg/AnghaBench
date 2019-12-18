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
 int /*<<< orphan*/  MIPI_CSIS_CMN_CTRL ; 
 int MIPI_CSIS_CMN_CTRL_RESET ; 
 int mipi_csis_read (struct csi_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_write (struct csi_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mipi_csis_sw_reset(struct csi_state *state)
{
	u32 val = mipi_csis_read(state, MIPI_CSIS_CMN_CTRL);

	mipi_csis_write(state, MIPI_CSIS_CMN_CTRL,
			val | MIPI_CSIS_CMN_CTRL_RESET);
	usleep_range(10, 20);
}