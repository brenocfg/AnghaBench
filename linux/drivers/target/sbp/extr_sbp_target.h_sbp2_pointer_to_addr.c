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
struct sbp2_pointer {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 sbp2_pointer_to_addr(const struct sbp2_pointer *ptr)
{
	return (u64)(be32_to_cpu(ptr->high) & 0x0000ffff) << 32 |
		(be32_to_cpu(ptr->low) & 0xfffffffc);
}