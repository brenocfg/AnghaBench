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
struct s2io_nic {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __S2IO_STATE_CARD_UP ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int is_s2io_card_up(const struct s2io_nic *sp)
{
	return test_bit(__S2IO_STATE_CARD_UP, &sp->state);
}