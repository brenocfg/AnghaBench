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
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  OP_ENDPTCOMPLETE ; 
 int ep_to_bit (struct ci_hdrc*,int) ; 
 int hw_test_and_clear (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_test_and_clear_complete(struct ci_hdrc *ci, int n)
{
	n = ep_to_bit(ci, n);
	return hw_test_and_clear(ci, OP_ENDPTCOMPLETE, BIT(n));
}