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
struct dm_block_manager {int /*<<< orphan*/  bufio; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bufio_prefetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void dm_bm_prefetch(struct dm_block_manager *bm, dm_block_t b)
{
	dm_bufio_prefetch(bm->bufio, b, 1);
}