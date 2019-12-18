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
struct slave {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  BOND_STATE_ACTIVE 129 
#define  BOND_STATE_BACKUP 128 
 int bond_slave_state (struct slave*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t state_show(struct slave *slave, char *buf)
{
	switch (bond_slave_state(slave)) {
	case BOND_STATE_ACTIVE:
		return sprintf(buf, "active\n");
	case BOND_STATE_BACKUP:
		return sprintf(buf, "backup\n");
	default:
		return sprintf(buf, "UNKNOWN\n");
	}
}