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
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFDPA_OP_FLAG_NOWAIT ; 
 int /*<<< orphan*/  ofdpa_port_fwd_disable (struct ofdpa_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ofdpa_port_stop(struct rocker_port *rocker_port)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;

	ofdpa_port_fwd_disable(ofdpa_port, OFDPA_OP_FLAG_NOWAIT);
}