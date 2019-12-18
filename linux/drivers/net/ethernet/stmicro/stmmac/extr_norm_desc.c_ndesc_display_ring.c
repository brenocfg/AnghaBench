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
typedef  int u64 ;
struct dma_desc {int /*<<< orphan*/  des3; int /*<<< orphan*/  des2; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__ virt_to_phys (struct dma_desc*) ; 

__attribute__((used)) static void ndesc_display_ring(void *head, unsigned int size, bool rx)
{
	struct dma_desc *p = (struct dma_desc *)head;
	int i;

	pr_info("%s descriptor ring:\n", rx ? "RX" : "TX");

	for (i = 0; i < size; i++) {
		u64 x;

		x = *(u64 *)p;
		pr_info("%03d [0x%x]: 0x%x 0x%x 0x%x 0x%x",
			i, (unsigned int)virt_to_phys(p),
			(unsigned int)x, (unsigned int)(x >> 32),
			p->des2, p->des3);
		p++;
	}
	pr_info("\n");
}