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
struct addr_req {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_wq ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_timeout(struct addr_req *req, unsigned long time)
{
	unsigned long delay;

	delay = time - jiffies;
	if ((long)delay < 0)
		delay = 0;

	mod_delayed_work(addr_wq, &req->work, delay);
}