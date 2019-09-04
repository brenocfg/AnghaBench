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
struct max2175 {int dummy; } ;

/* Variables and functions */
 int max2175_poll_timeout (struct max2175*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxm_err (struct max2175*,char*) ; 

__attribute__((used)) static int max2175_poll_csm_ready(struct max2175 *ctx)
{
	int ret;

	ret = max2175_poll_timeout(ctx, 69, 1, 1, 0, 50000);
	if (ret)
		mxm_err(ctx, "csm not ready\n");

	return ret;
}