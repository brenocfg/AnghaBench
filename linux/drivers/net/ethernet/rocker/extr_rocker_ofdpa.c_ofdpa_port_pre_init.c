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
struct rocker_port {int /*<<< orphan*/  pport; int /*<<< orphan*/  dev; TYPE_1__* rocker; struct ofdpa_port* wpriv; } ;
struct ofdpa_port {int /*<<< orphan*/  ageing_time; int /*<<< orphan*/  brport_flags; int /*<<< orphan*/  pport; int /*<<< orphan*/  dev; struct rocker_port* rocker_port; int /*<<< orphan*/  ofdpa; } ;
struct TYPE_2__ {int /*<<< orphan*/  wpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_DEFAULT_AGEING_TIME ; 
 int /*<<< orphan*/  BR_LEARNING ; 

__attribute__((used)) static int ofdpa_port_pre_init(struct rocker_port *rocker_port)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;

	ofdpa_port->ofdpa = rocker_port->rocker->wpriv;
	ofdpa_port->rocker_port = rocker_port;
	ofdpa_port->dev = rocker_port->dev;
	ofdpa_port->pport = rocker_port->pport;
	ofdpa_port->brport_flags = BR_LEARNING;
	ofdpa_port->ageing_time = BR_DEFAULT_AGEING_TIME;
	return 0;
}