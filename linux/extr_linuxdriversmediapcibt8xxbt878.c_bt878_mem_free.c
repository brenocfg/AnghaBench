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
struct bt878 {int /*<<< orphan*/ * risc_cpu; int /*<<< orphan*/  risc_dma; int /*<<< orphan*/  risc_size; int /*<<< orphan*/  dev; int /*<<< orphan*/ * buf_cpu; int /*<<< orphan*/  buf_dma; int /*<<< orphan*/  buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt878_mem_free(struct bt878 *bt)
{
	if (bt->buf_cpu) {
		pci_free_consistent(bt->dev, bt->buf_size, bt->buf_cpu,
				    bt->buf_dma);
		bt->buf_cpu = NULL;
	}

	if (bt->risc_cpu) {
		pci_free_consistent(bt->dev, bt->risc_size, bt->risc_cpu,
				    bt->risc_dma);
		bt->risc_cpu = NULL;
	}
}