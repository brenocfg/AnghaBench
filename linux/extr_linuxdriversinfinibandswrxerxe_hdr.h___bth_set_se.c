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
struct rxe_bth {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTH_SE_MASK ; 

__attribute__((used)) static inline void __bth_set_se(void *arg, int se)
{
	struct rxe_bth *bth = arg;

	if (se)
		bth->flags |= BTH_SE_MASK;
	else
		bth->flags &= ~BTH_SE_MASK;
}