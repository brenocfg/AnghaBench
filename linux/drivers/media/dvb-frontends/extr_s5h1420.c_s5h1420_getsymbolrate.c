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
typedef  int /*<<< orphan*/  u32 ;
struct s5h1420_state {int /*<<< orphan*/  symbol_rate; } ;

/* Variables and functions */

__attribute__((used)) static u32 s5h1420_getsymbolrate(struct s5h1420_state* state)
{
	return state->symbol_rate;
}