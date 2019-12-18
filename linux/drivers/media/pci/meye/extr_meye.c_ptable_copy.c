#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * mchip_ptable; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ meye ; 

__attribute__((used)) static void ptable_copy(u8 *buf, int start, int size, int pt_pages)
{
	int i;

	for (i = 0; i < (size / PAGE_SIZE) * PAGE_SIZE; i += PAGE_SIZE) {
		memcpy(buf + i, meye.mchip_ptable[start++], PAGE_SIZE);
		if (start >= pt_pages)
			start = 0;
	}
	memcpy(buf + i, meye.mchip_ptable[start], size % PAGE_SIZE);
}