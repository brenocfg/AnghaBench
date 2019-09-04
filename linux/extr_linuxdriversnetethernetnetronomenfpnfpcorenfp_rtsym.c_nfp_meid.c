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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static int nfp_meid(u8 island_id, u8 menum)
{
	return (island_id & 0x3F) == island_id && menum < 12 ?
		(island_id << 4) | (menum + 4) : -1;
}