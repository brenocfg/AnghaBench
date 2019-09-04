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
 int BTH_PAD_MASK ; 

__attribute__((used)) static inline void __bth_set_pad(void *arg, u8 pad)
{
	struct rxe_bth *bth = arg;

	bth->flags = (BTH_PAD_MASK & (pad << 4)) |
			(~BTH_PAD_MASK & bth->flags);
}