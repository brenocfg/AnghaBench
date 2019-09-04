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
typedef  int u8 ;
struct rxe_bth {int flags; } ;

/* Variables and functions */
 int BTH_MIG_MASK ; 

__attribute__((used)) static inline u8 __bth_mig(void *arg)
{
	struct rxe_bth *bth = arg;

	return 0 != (BTH_MIG_MASK & bth->flags);
}