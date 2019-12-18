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
struct slave {int /*<<< orphan*/  link; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* bond_slave_link_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t mii_status_show(struct slave *slave, char *buf)
{
	return sprintf(buf, "%s\n", bond_slave_link_status(slave->link));
}