#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* remove_frontend ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ dmx; } ;
struct dvb_bt8xx_card {int /*<<< orphan*/  dvb_adapter; scalar_t__ fe; TYPE_3__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  fe_hw; int /*<<< orphan*/  fe_mem; int /*<<< orphan*/  dvbnet; TYPE_4__* bt; int /*<<< orphan*/  bttv_nr; } ;
struct bttv_sub_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt878_stop (TYPE_4__*) ; 
 struct dvb_bt8xx_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_3__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (scalar_t__) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dvb_bt8xx_card*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dvb_bt8xx_remove(struct bttv_sub_device *sub)
{
	struct dvb_bt8xx_card *card = dev_get_drvdata(&sub->dev);

	dprintk("dvb_bt8xx: unloading card%d\n", card->bttv_nr);

	bt878_stop(card->bt);
	tasklet_kill(&card->bt->tasklet);
	dvb_net_release(&card->dvbnet);
	card->demux.dmx.remove_frontend(&card->demux.dmx, &card->fe_mem);
	card->demux.dmx.remove_frontend(&card->demux.dmx, &card->fe_hw);
	dvb_dmxdev_release(&card->dmxdev);
	dvb_dmx_release(&card->demux);
	if (card->fe) {
		dvb_unregister_frontend(card->fe);
		dvb_frontend_detach(card->fe);
	}
	dvb_unregister_adapter(&card->dvb_adapter);

	kfree(card);
}