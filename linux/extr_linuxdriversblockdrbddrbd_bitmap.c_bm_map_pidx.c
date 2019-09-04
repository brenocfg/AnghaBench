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
struct drbd_bitmap {int dummy; } ;

/* Variables and functions */
 unsigned long* __bm_map_pidx (struct drbd_bitmap*,unsigned int) ; 

__attribute__((used)) static unsigned long *bm_map_pidx(struct drbd_bitmap *b, unsigned int idx)
{
	return __bm_map_pidx(b, idx);
}