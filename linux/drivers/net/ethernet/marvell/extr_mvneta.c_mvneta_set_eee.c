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
typedef  int /*<<< orphan*/  u32 ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_LPI_CTRL_1 ; 
 int /*<<< orphan*/  MVNETA_LPI_REQUEST_ENABLE ; 
 int /*<<< orphan*/  mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_set_eee(struct mvneta_port *pp, bool enable)
{
	u32 lpi_ctl1;

	lpi_ctl1 = mvreg_read(pp, MVNETA_LPI_CTRL_1);
	if (enable)
		lpi_ctl1 |= MVNETA_LPI_REQUEST_ENABLE;
	else
		lpi_ctl1 &= ~MVNETA_LPI_REQUEST_ENABLE;
	mvreg_write(pp, MVNETA_LPI_CTRL_1, lpi_ctl1);
}