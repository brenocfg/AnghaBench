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
struct solo_dev {int nr_chans; int /*<<< orphan*/  vh_dma; scalar_t__ vh_buf; int /*<<< orphan*/  vh_size; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * v4l2_enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_enc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_ring_stop (struct solo_dev*) ; 

void solo_enc_v4l2_exit(struct solo_dev *solo_dev)
{
	int i;

	solo_ring_stop(solo_dev);

	for (i = 0; i < solo_dev->nr_chans; i++)
		solo_enc_free(solo_dev->v4l2_enc[i]);

	if (solo_dev->vh_buf)
		pci_free_consistent(solo_dev->pdev, solo_dev->vh_size,
			    solo_dev->vh_buf, solo_dev->vh_dma);
}