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
struct reset_control_array {unsigned int num_rstcs; int /*<<< orphan*/ * rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_control_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_control_array_release(struct reset_control_array *resets)
{
	unsigned int i;

	for (i = 0; i < resets->num_rstcs; i++)
		reset_control_release(resets->rstc[i]);
}