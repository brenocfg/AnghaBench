#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
struct mv_cesa_op_ctx {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 mv_cesa_get_op_cfg(const struct mv_cesa_op_ctx *op)
{
	return le32_to_cpu(op->desc.config);
}