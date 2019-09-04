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
typedef  int u64 ;
struct flcn_u64 {int lo; scalar_t__ hi; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 flcn64_to_u64(const struct flcn_u64 f)
{
	return ((u64)f.hi) << 32 | f.lo;
}