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
struct nullb_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */

__attribute__((used)) static inline void null_zone_write(struct nullb_cmd *cmd, sector_t sector,
				   unsigned int nr_sectors)
{
}