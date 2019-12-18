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
struct das16_private_struct {int /*<<< orphan*/  dma; int /*<<< orphan*/  timer; } ;
struct comedi_device {struct das16_private_struct* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_isadma_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void das16_free_dma(struct comedi_device *dev)
{
	struct das16_private_struct *devpriv = dev->private;

	if (devpriv) {
		del_timer_sync(&devpriv->timer);
		comedi_isadma_free(devpriv->dma);
	}
}