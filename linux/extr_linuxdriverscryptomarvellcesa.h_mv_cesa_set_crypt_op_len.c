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
struct TYPE_2__ {int /*<<< orphan*/  enc_len; } ;
struct mv_cesa_op_ctx {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline void mv_cesa_set_crypt_op_len(struct mv_cesa_op_ctx *op, int len)
{
	op->desc.enc_len = cpu_to_le32(len);
}