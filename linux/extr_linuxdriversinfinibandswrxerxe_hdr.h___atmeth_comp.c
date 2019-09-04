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
struct rxe_atmeth {int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 __atmeth_comp(void *arg)
{
	struct rxe_atmeth *atmeth = arg;

	return be64_to_cpu(atmeth->comp);
}