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
struct map_info {int dummy; } ;
typedef  int /*<<< orphan*/  map_word ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inline_map_write (struct map_info*,int /*<<< orphan*/  const,unsigned long) ; 
 int /*<<< orphan*/  octeon_bootbus_sem ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void octeon_flash_map_write(struct map_info *map, const map_word datum,
				   unsigned long ofs)
{
	down(&octeon_bootbus_sem);
	inline_map_write(map, datum, ofs);
	up(&octeon_bootbus_sem);
}