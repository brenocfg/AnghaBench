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
struct ioatdma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  compl_write; int /*<<< orphan*/  int_en; int /*<<< orphan*/  op; } ;
struct ioat_dma_descriptor {TYPE_1__ ctl_f; int /*<<< orphan*/  ctl; scalar_t__ next; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  flags; int /*<<< orphan*/  cookie; scalar_t__ phys; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,unsigned long long,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* to_dev (struct ioatdma_chan*) ; 

__attribute__((used)) static inline void
__dump_desc_dbg(struct ioatdma_chan *ioat_chan, struct ioat_dma_descriptor *hw,
		struct dma_async_tx_descriptor *tx, int id)
{
	struct device *dev = to_dev(ioat_chan);

	dev_dbg(dev, "desc[%d]: (%#llx->%#llx) cookie: %d flags: %#x"
		" ctl: %#10.8x (op: %#x int_en: %d compl: %d)\n", id,
		(unsigned long long) tx->phys,
		(unsigned long long) hw->next, tx->cookie, tx->flags,
		hw->ctl, hw->ctl_f.op, hw->ctl_f.int_en, hw->ctl_f.compl_write);
}