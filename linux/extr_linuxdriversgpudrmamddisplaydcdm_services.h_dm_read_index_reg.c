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
typedef  int /*<<< orphan*/  uint32_t ;
struct dc_context {int /*<<< orphan*/  cgs_device; } ;
typedef  enum cgs_ind_reg { ____Placeholder_cgs_ind_reg } cgs_ind_reg ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_read_ind_register (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t dm_read_index_reg(
	const struct dc_context *ctx,
	enum cgs_ind_reg addr_space,
	uint32_t index)
{
	return cgs_read_ind_register(ctx->cgs_device, addr_space, index);
}