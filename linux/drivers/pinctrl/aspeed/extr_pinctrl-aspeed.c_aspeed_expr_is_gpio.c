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
struct aspeed_sig_expr {int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool aspeed_expr_is_gpio(const struct aspeed_sig_expr *expr)
{
	/*
	 * The signal type is GPIO if the signal name has "GPIO" as a prefix.
	 * strncmp (rather than strcmp) is used to implement the prefix
	 * requirement.
	 *
	 * expr->signal might look like "GPIOT3" in the GPIO case.
	 */
	return strncmp(expr->signal, "GPIO", 4) == 0;
}