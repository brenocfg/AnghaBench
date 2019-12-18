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
typedef  int u32 ;
struct rxe_rdeth {int /*<<< orphan*/  een; } ;

/* Variables and functions */
 int RDETH_EEN_MASK ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static inline void __rdeth_set_een(void *arg, u32 een)
{
	struct rxe_rdeth *rdeth = arg;

	rdeth->een = cpu_to_be32(RDETH_EEN_MASK & een);
}