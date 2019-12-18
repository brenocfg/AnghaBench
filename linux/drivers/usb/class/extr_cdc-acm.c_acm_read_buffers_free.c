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
struct acm {int rx_buflimit; TYPE_1__* read_buffers; int /*<<< orphan*/  readsize; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acm_read_buffers_free(struct acm *acm)
{
	int i;

	for (i = 0; i < acm->rx_buflimit; i++)
		usb_free_coherent(acm->dev, acm->readsize,
			  acm->read_buffers[i].base, acm->read_buffers[i].dma);
}