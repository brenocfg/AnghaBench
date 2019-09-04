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
typedef  int /*<<< orphan*/  uint32_t ;
struct sg_mapping_iter {scalar_t__ consumed; int /*<<< orphan*/  addr; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 size_t min (scalar_t__,size_t) ; 
 scalar_t__ sg_dwiter_next (struct sg_mapping_iter*) ; 

__attribute__((used)) static void sg_dwiter_write_slow(struct sg_mapping_iter *miter, uint32_t data)
{
	size_t len, left = 4;
	void *addr = &data;

	do {
		len = min(miter->length - miter->consumed, left);
		memcpy(miter->addr, addr, len);
		miter->consumed += len;
		left -= len;
		if (!left)
			return;
		addr += len;
	} while (sg_dwiter_next(miter));
}