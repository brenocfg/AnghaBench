#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_fdma_dev {struct st_fdma_chan* chans; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct st_fdma_chan {TYPE_2__ vchan; TYPE_1__* fdesc; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_5__ {TYPE_3__ vdesc; int /*<<< orphan*/  iscyclic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_COMPLETE ; 
 int /*<<< orphan*/  FDMA_INT_CLR_OFST ; 
 unsigned long FDMA_INT_STA_CH ; 
 unsigned long FDMA_INT_STA_ERR ; 
 int /*<<< orphan*/  FDMA_INT_STA_OFST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long fdma_read (struct st_fdma_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdma_write (struct st_fdma_dev*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_fdma_ch_sta_update (struct st_fdma_chan*,unsigned long) ; 
 int /*<<< orphan*/  st_fdma_xfer_desc (struct st_fdma_chan*) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_3__*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (TYPE_3__*) ; 

__attribute__((used)) static irqreturn_t st_fdma_irq_handler(int irq, void *dev_id)
{
	struct st_fdma_dev *fdev = dev_id;
	irqreturn_t ret = IRQ_NONE;
	struct st_fdma_chan *fchan = &fdev->chans[0];
	unsigned long int_sta, clr;

	int_sta = fdma_read(fdev, FDMA_INT_STA_OFST);
	clr = int_sta;

	for (; int_sta != 0 ; int_sta >>= 2, fchan++) {
		if (!(int_sta & (FDMA_INT_STA_CH | FDMA_INT_STA_ERR)))
			continue;

		spin_lock(&fchan->vchan.lock);
		st_fdma_ch_sta_update(fchan, int_sta);

		if (fchan->fdesc) {
			if (!fchan->fdesc->iscyclic) {
				list_del(&fchan->fdesc->vdesc.node);
				vchan_cookie_complete(&fchan->fdesc->vdesc);
				fchan->fdesc = NULL;
				fchan->status = DMA_COMPLETE;
			} else {
				vchan_cyclic_callback(&fchan->fdesc->vdesc);
			}

			/* Start the next descriptor (if available) */
			if (!fchan->fdesc)
				st_fdma_xfer_desc(fchan);
		}

		spin_unlock(&fchan->vchan.lock);
		ret = IRQ_HANDLED;
	}

	fdma_write(fdev, clr, FDMA_INT_CLR_OFST);

	return ret;
}