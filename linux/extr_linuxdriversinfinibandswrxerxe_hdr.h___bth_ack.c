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
struct rxe_bth {int apsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTH_ACK_MASK ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __bth_ack(void *arg)
{
	struct rxe_bth *bth = arg;

	return 0 != (cpu_to_be32(BTH_ACK_MASK) & bth->apsn);
}