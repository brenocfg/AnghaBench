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
typedef  int u8 ;
struct si2165_state {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_INIT_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int si2165_readreg8 (struct si2165_state*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int si2165_wait_init_done(struct si2165_state *state)
{
	int ret;
	u8 val = 0;
	int i;

	for (i = 0; i < 3; ++i) {
		ret = si2165_readreg8(state, REG_INIT_DONE, &val);
		if (ret < 0)
			return ret;
		if (val == 0x01)
			return 0;
		usleep_range(1000, 50000);
	}
	dev_err(&state->client->dev, "init_done was not set\n");
	return -EINVAL;
}