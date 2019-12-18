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
struct intel_uncore_forcewake_domain {int dummy; } ;

/* Variables and functions */
 int __wait_for_ack (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
wait_ack_clear(const struct intel_uncore_forcewake_domain *d,
	       const u32 ack)
{
	return __wait_for_ack(d, ack, 0);
}