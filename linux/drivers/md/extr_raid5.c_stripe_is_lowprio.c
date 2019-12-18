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
struct stripe_head {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  STRIPE_R5C_FULL_STRIPE ; 
 int /*<<< orphan*/  STRIPE_R5C_PARTIAL_STRIPE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool stripe_is_lowprio(struct stripe_head *sh)
{
	return (test_bit(STRIPE_R5C_FULL_STRIPE, &sh->state) ||
		test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state)) &&
	       !test_bit(STRIPE_R5C_CACHING, &sh->state);
}