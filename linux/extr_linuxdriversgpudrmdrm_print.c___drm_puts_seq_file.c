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
struct drm_printer {int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_puts (int /*<<< orphan*/ ,char const*) ; 

void __drm_puts_seq_file(struct drm_printer *p, const char *str)
{
	seq_puts(p->arg, str);
}