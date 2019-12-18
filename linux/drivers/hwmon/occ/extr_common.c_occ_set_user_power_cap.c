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
typedef  int u8 ;
typedef  int u16 ;
struct occ {int (* send_cmd ) (struct occ*,int*) ;int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct occ*,int*) ; 

__attribute__((used)) static int occ_set_user_power_cap(struct occ *occ, u16 user_power_cap)
{
	int rc;
	u8 cmd[8];
	u16 checksum = 0x24;
	__be16 user_power_cap_be = cpu_to_be16(user_power_cap);

	cmd[0] = 0;
	cmd[1] = 0x22;
	cmd[2] = 0;
	cmd[3] = 2;

	memcpy(&cmd[4], &user_power_cap_be, 2);

	checksum += cmd[4] + cmd[5];
	cmd[6] = checksum >> 8;
	cmd[7] = checksum & 0xFF;

	rc = mutex_lock_interruptible(&occ->lock);
	if (rc)
		return rc;

	rc = occ->send_cmd(occ, cmd);

	mutex_unlock(&occ->lock);

	return rc;
}