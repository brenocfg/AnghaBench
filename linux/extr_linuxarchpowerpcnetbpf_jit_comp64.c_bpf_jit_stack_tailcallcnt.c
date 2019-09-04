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
struct codegen_context {int dummy; } ;

/* Variables and functions */
 int bpf_jit_stack_local (struct codegen_context*) ; 

__attribute__((used)) static int bpf_jit_stack_tailcallcnt(struct codegen_context *ctx)
{
	return bpf_jit_stack_local(ctx) + 8;
}