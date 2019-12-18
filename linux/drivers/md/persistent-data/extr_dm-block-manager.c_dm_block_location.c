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
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bufio_get_block_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_buffer (struct dm_block*) ; 

dm_block_t dm_block_location(struct dm_block *b)
{
	return dm_bufio_get_block_number(to_buffer(b));
}