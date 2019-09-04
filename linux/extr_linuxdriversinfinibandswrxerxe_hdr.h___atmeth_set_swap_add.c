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
typedef  int /*<<< orphan*/  u64 ;
struct rxe_atmeth {int /*<<< orphan*/  swap_add; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __atmeth_set_swap_add(void *arg, u64 swap_add)
{
	struct rxe_atmeth *atmeth = arg;

	atmeth->swap_add = cpu_to_be64(swap_add);
}