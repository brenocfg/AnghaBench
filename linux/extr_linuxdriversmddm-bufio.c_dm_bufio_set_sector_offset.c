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
struct dm_bufio_client {int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */

void dm_bufio_set_sector_offset(struct dm_bufio_client *c, sector_t start)
{
	c->start = start;
}