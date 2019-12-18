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
struct uclogic_params {int invalid; } ;

/* Variables and functions */

__attribute__((used)) static void uclogic_params_init_invalid(struct uclogic_params *params)
{
	params->invalid = true;
}