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
typedef  int u16 ;
struct TYPE_2__ {int flow_control; } ;
struct r8152 {TYPE_1__ ups_info; } ;

/* Variables and functions */
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int r8152_mdio_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r8152b_enable_fc(struct r8152 *tp)
{
	u16 anar;

	anar = r8152_mdio_read(tp, MII_ADVERTISE);
	anar |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
	r8152_mdio_write(tp, MII_ADVERTISE, anar);

	tp->ups_info.flow_control = true;
}