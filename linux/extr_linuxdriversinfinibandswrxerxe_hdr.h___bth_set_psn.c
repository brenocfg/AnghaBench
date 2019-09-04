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
struct rxe_bth {int /*<<< orphan*/  apsn; } ;

/* Variables and functions */
 int BTH_PSN_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static inline void __bth_set_psn(void *arg, u32 psn)
{
	struct rxe_bth *bth = arg;
	u32 apsn = be32_to_cpu(bth->apsn);

	bth->apsn = cpu_to_be32((BTH_PSN_MASK & psn) |
			(~BTH_PSN_MASK & apsn));
}