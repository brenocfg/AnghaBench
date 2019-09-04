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
struct sii9234 {int i2c_error; } ;

/* Variables and functions */

__attribute__((used)) static int sii9234_clear_error(struct sii9234 *ctx)
{
	int ret = ctx->i2c_error;

	ctx->i2c_error = 0;

	return ret;
}