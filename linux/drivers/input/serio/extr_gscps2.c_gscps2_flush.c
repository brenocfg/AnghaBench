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
struct gscps2port {scalar_t__ append; scalar_t__ act; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int GSC_STAT_RBNE ; 
 int /*<<< orphan*/  gscps2_readb_input (int /*<<< orphan*/ ) ; 
 int gscps2_readb_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gscps2_flush(struct gscps2port *ps2port)
{
	while (gscps2_readb_status(ps2port->addr) & GSC_STAT_RBNE)
		gscps2_readb_input(ps2port->addr);
	ps2port->act = ps2port->append = 0;
}