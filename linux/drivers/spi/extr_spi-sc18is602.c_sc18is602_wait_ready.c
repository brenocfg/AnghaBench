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
struct sc18is602 {int speed; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sc18is602_wait_ready(struct sc18is602 *hw, int len)
{
	int i, err;
	int usecs = 1000000 * len / hw->speed + 1;
	u8 dummy[1];

	for (i = 0; i < 10; i++) {
		err = i2c_master_recv(hw->client, dummy, 1);
		if (err >= 0)
			return 0;
		usleep_range(usecs, usecs * 2);
	}
	return -ETIMEDOUT;
}