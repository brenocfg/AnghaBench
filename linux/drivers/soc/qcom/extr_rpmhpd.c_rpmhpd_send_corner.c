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
struct tcs_cmd {unsigned int data; int /*<<< orphan*/  addr; } ;
struct rpmhpd {int /*<<< orphan*/  dev; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int rpmh_write (int /*<<< orphan*/ ,int,struct tcs_cmd*,int) ; 
 int rpmh_write_async (int /*<<< orphan*/ ,int,struct tcs_cmd*,int) ; 

__attribute__((used)) static int rpmhpd_send_corner(struct rpmhpd *pd, int state,
			      unsigned int corner, bool sync)
{
	struct tcs_cmd cmd = {
		.addr = pd->addr,
		.data = corner,
	};

	/*
	 * Wait for an ack only when we are increasing the
	 * perf state of the power domain
	 */
	if (sync)
		return rpmh_write(pd->dev, state, &cmd, 1);
	else
		return rpmh_write_async(pd->dev, state, &cmd, 1);
}