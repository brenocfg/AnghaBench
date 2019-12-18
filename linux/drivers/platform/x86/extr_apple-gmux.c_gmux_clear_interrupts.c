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
typedef  int /*<<< orphan*/  u8 ;
struct apple_gmux_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMUX_PORT_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  gmux_interrupt_get_status (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_write8 (struct apple_gmux_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gmux_clear_interrupts(struct apple_gmux_data *gmux_data)
{
	u8 status;

	/* to clear interrupts write back current status */
	status = gmux_interrupt_get_status(gmux_data);
	gmux_write8(gmux_data, GMUX_PORT_INTERRUPT_STATUS, status);
}