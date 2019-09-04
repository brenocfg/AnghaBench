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
struct dm_bufio_client {int dummy; } ;
struct dm_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  NF_GET ; 
 void* new_read (struct dm_bufio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_buffer**) ; 

void *dm_bufio_get(struct dm_bufio_client *c, sector_t block,
		   struct dm_buffer **bp)
{
	return new_read(c, block, NF_GET, bp);
}