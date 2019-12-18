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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ROCE_BITMAP_SZ ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_bitmap ; 

int usnic_transport_init(void)
{
	roce_bitmap = kzalloc(ROCE_BITMAP_SZ, GFP_KERNEL);
	if (!roce_bitmap)
		return -ENOMEM;

	/* Do not ever allocate bit 0, hence set it here */
	bitmap_set(roce_bitmap, 0, 1);
	return 0;
}