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
struct xpc_partition {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
xpc_teardown_ch_structures_uv(struct xpc_partition *part)
{
	/* nothing needs to be done */
	return;
}