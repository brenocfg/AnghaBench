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
struct pt_regs {int dummy; } ;
struct perf_callchain_entry_ctx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void perf_callchain_user_64(struct perf_callchain_entry_ctx *entry,
					  struct pt_regs *regs)
{
}