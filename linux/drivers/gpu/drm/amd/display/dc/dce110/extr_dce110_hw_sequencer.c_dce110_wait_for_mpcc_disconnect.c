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
struct resource_pool {int dummy; } ;
struct pipe_ctx {int dummy; } ;
struct dc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dce110_wait_for_mpcc_disconnect(
		struct dc *dc,
		struct resource_pool *res_pool,
		struct pipe_ctx *pipe_ctx)
{
	/* do nothing*/
}