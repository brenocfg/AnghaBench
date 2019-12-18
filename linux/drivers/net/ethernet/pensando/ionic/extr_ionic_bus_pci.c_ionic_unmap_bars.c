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
struct ionic_dev_bar {scalar_t__ len; int /*<<< orphan*/ * vaddr; scalar_t__ bus_addr; } ;
struct ionic {struct ionic_dev_bar* bars; } ;

/* Variables and functions */
 unsigned int IONIC_BARS_MAX ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_unmap_bars(struct ionic *ionic)
{
	struct ionic_dev_bar *bars = ionic->bars;
	unsigned int i;

	for (i = 0; i < IONIC_BARS_MAX; i++) {
		if (bars[i].vaddr) {
			iounmap(bars[i].vaddr);
			bars[i].bus_addr = 0;
			bars[i].vaddr = NULL;
			bars[i].len = 0;
		}
	}
}