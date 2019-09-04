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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_FRESH ; 
 int /*<<< orphan*/  dm_bufio_in_request () ; 
 void* new_read (struct dm_bufio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_buffer**) ; 

void *dm_bufio_new(struct dm_bufio_client *c, sector_t block,
		   struct dm_buffer **bp)
{
	BUG_ON(dm_bufio_in_request());

	return new_read(c, block, NF_FRESH, bp);
}