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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_class_host_incr_syncpt (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  host1x_opcode_imm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_uclass_incr_syncpt_r () ; 

__attribute__((used)) static inline u32 host1x_opcode_imm_incr_syncpt(unsigned cond, unsigned indx)
{
	return host1x_opcode_imm(host1x_uclass_incr_syncpt_r(),
		host1x_class_host_incr_syncpt(cond, indx));
}