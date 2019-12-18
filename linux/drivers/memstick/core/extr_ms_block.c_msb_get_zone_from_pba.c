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
 int MS_BLOCKS_IN_ZONE ; 

__attribute__((used)) static int msb_get_zone_from_pba(int pba)
{
	return pba / MS_BLOCKS_IN_ZONE;
}