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
struct net_device {scalar_t__ mem_start; } ;

/* Variables and functions */
 int WD_START_PG ; 
 int /*<<< orphan*/  word_memcpy_tocard (scalar_t__,unsigned char const*,int) ; 

__attribute__((used)) static void slow_sane_block_output(struct net_device *dev, int count,
				   const unsigned char *buf, int start_page)
{
	long shmem = (start_page - WD_START_PG)<<8;

	word_memcpy_tocard(dev->mem_start + shmem, buf, count);
}