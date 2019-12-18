#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct lpc32xx_udc {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* conn_chgb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uda_power_event(struct lpc32xx_udc *udc, u32 conn)
{
	/* Just notify of a connection change event (optional) */
	if (udc->board->conn_chgb != NULL)
		udc->board->conn_chgb(conn);
}