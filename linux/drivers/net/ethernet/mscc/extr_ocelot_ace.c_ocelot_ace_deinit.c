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

/* Variables and functions */
 int /*<<< orphan*/  acl_block ; 
 int /*<<< orphan*/  ocelot_acl_block_destroy (int /*<<< orphan*/ ) ; 

void ocelot_ace_deinit(void)
{
	ocelot_acl_block_destroy(acl_block);
}