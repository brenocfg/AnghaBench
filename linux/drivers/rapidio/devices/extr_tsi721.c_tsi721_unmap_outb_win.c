#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u16 ;
struct tsi721_ob_win {int active; scalar_t__ destid; scalar_t__ rstart; scalar_t__ base; scalar_t__ size; TYPE_2__* pbar; } ;
struct tsi721_device {int /*<<< orphan*/  obwin_cnt; scalar_t__ regs; TYPE_1__* pdev; struct tsi721_ob_win* ob_win; } ;
struct rio_mport {struct tsi721_device* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  free; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBW ; 
 scalar_t__ TSI721_OBWINLB (int) ; 
 int TSI721_OBWIN_NUM ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,scalar_t__) ; 

__attribute__((used)) static void tsi721_unmap_outb_win(struct rio_mport *mport,
				  u16 destid, u64 rstart)
{
	struct tsi721_device *priv = mport->priv;
	struct tsi721_ob_win *ob_win;
	int i;

	tsi_debug(OBW, &priv->pdev->dev, "did=%d ra=0x%llx", destid, rstart);

	for (i = 0; i < TSI721_OBWIN_NUM; i++) {
		ob_win = &priv->ob_win[i];

		if (ob_win->active &&
		    ob_win->destid == destid && ob_win->rstart == rstart) {
			tsi_debug(OBW, &priv->pdev->dev,
				  "free OBW%d @%llx", i, ob_win->base);
			ob_win->active = false;
			iowrite32(0, priv->regs + TSI721_OBWINLB(i));
			ob_win->pbar->free += ob_win->size;
			priv->obwin_cnt++;
			break;
		}
	}
}