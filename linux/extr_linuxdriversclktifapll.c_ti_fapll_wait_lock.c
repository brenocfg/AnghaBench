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
typedef  int u32 ;
struct fapll_data {int /*<<< orphan*/  name; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int FAPLL_MAIN_LOCK ; 
 int FAPLL_MAX_RETRIES ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ti_fapll_wait_lock(struct fapll_data *fd)
{
	int retries = FAPLL_MAX_RETRIES;
	u32 v;

	while ((v = readl_relaxed(fd->base))) {
		if (v & FAPLL_MAIN_LOCK)
			return 0;

		if (retries-- <= 0)
			break;

		udelay(1);
	}

	pr_err("%s failed to lock\n", fd->name);

	return -ETIMEDOUT;
}