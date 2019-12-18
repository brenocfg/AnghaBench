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
struct ld9040 {int error; } ;

/* Variables and functions */

__attribute__((used)) static int ld9040_clear_error(struct ld9040 *ctx)
{
	int ret = ctx->error;

	ctx->error = 0;
	return ret;
}