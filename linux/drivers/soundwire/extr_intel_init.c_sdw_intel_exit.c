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
struct sdw_intel_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sdw_intel_ctx*) ; 
 int /*<<< orphan*/  sdw_intel_cleanup_pdev (struct sdw_intel_ctx*) ; 

void sdw_intel_exit(void *arg)
{
	struct sdw_intel_ctx *ctx = arg;

	sdw_intel_cleanup_pdev(ctx);
	kfree(ctx);
}