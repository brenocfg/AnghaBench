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
typedef  int uint32_t ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int dm_read_reg_soc15 (struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCC_DC_PIPE_DIS ; 

__attribute__((used)) static uint32_t read_pipe_fuses(struct dc_context *ctx)
{
	uint32_t value = dm_read_reg_soc15(ctx, mmCC_DC_PIPE_DIS, 0);
	/* RV1 support max 4 pipes */
	value = value & 0xf;
	return value;
}