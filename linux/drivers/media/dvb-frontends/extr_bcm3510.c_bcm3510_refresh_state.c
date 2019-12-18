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
struct bcm3510_state {int status_check_interval; scalar_t__ next_status_check; int /*<<< orphan*/  status2; int /*<<< orphan*/  status1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STATUS ; 
 int HZ ; 
 int /*<<< orphan*/  MSGID_STATUS1 ; 
 int /*<<< orphan*/  MSGID_STATUS2 ; 
 int /*<<< orphan*/  bcm3510_do_hab_cmd (struct bcm3510_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int bcm3510_refresh_state(struct bcm3510_state *st)
{
	if (time_after(jiffies,st->next_status_check)) {
		bcm3510_do_hab_cmd(st, CMD_STATUS, MSGID_STATUS1, NULL,0, (u8 *)&st->status1, sizeof(st->status1));
		bcm3510_do_hab_cmd(st, CMD_STATUS, MSGID_STATUS2, NULL,0, (u8 *)&st->status2, sizeof(st->status2));
		st->next_status_check = jiffies + (st->status_check_interval*HZ)/1000;
	}
	return 0;
}