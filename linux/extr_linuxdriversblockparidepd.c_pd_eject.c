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
struct pd_unit {int dummy; } ;
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
 int /*<<< orphan*/  DBMSG (char*) ; 
 int /*<<< orphan*/  IDE_DOORUNLOCK ; 
 int /*<<< orphan*/  IDE_EJECT ; 
 int Ok ; 
 int /*<<< orphan*/  pd_send_command (struct pd_unit*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_wait_for (struct pd_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum action pd_eject(struct pd_unit *disk)
{
	pd_wait_for(disk, 0, DBMSG("before unlock on eject"));
	pd_send_command(disk, 1, 0, 0, 0, 0, IDE_DOORUNLOCK);
	pd_wait_for(disk, 0, DBMSG("after unlock on eject"));
	pd_wait_for(disk, 0, DBMSG("before eject"));
	pd_send_command(disk, 0, 0, 0, 0, 0, IDE_EJECT);
	pd_wait_for(disk, 0, DBMSG("after eject"));
	return Ok;
}