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
typedef  scalar_t__ u8 ;
struct rxe_bth {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTH_MIG_MASK ; 

__attribute__((used)) static inline void __bth_set_mig(void *arg, u8 mig)
{
	struct rxe_bth *bth = arg;

	if (mig)
		bth->flags |= BTH_MIG_MASK;
	else
		bth->flags &= ~BTH_MIG_MASK;
}