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
typedef  int /*<<< orphan*/  u64 ;
struct cxl_context {int /*<<< orphan*/  kernel; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_calculate_sr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_is_power9 () ; 

__attribute__((used)) static u64 calculate_sr(struct cxl_context *ctx)
{
	return cxl_calculate_sr(ctx->master, ctx->kernel, false,
				cxl_is_power9());
}