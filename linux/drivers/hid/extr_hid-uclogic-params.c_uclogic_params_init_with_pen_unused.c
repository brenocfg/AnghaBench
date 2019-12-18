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
struct uclogic_params {int pen_unused; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct uclogic_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uclogic_params_init_with_pen_unused(struct uclogic_params *params)
{
	memset(params, 0, sizeof(*params));
	params->pen_unused = true;
}