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
struct aspeed_pin_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_sig_expr_function ; 
 char* get_defined_attribute (struct aspeed_pin_desc const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *get_defined_functions(const struct aspeed_pin_desc *pdesc)
{
	return get_defined_attribute(pdesc, aspeed_sig_expr_function);
}