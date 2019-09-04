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
 int cvmx_bootmem_phy_named_block_free (char*,int /*<<< orphan*/ ) ; 

int cvmx_bootmem_free_named(char *name)
{
	return cvmx_bootmem_phy_named_block_free(name, 0);
}