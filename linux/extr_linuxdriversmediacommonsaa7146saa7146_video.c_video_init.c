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
struct TYPE_4__ {struct saa7146_dev* dev; int /*<<< orphan*/  timeout; int /*<<< orphan*/  queue; } ;
struct saa7146_vv {int /*<<< orphan*/  current_hps_sync; int /*<<< orphan*/  current_hps_source; int /*<<< orphan*/ * standard; TYPE_2__ video_dmaq; } ;
struct saa7146_dev {TYPE_1__* ext_vv_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * stds; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAA7146_HPS_SOURCE_PORT_A ; 
 int /*<<< orphan*/  SAA7146_HPS_SYNC_PORT_A ; 
 int /*<<< orphan*/  saa7146_buffer_timeout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void video_init(struct saa7146_dev *dev, struct saa7146_vv *vv)
{
	INIT_LIST_HEAD(&vv->video_dmaq.queue);

	timer_setup(&vv->video_dmaq.timeout, saa7146_buffer_timeout, 0);
	vv->video_dmaq.dev              = dev;

	/* set some default values */
	vv->standard = &dev->ext_vv_data->stds[0];

	/* FIXME: what's this? */
	vv->current_hps_source = SAA7146_HPS_SOURCE_PORT_A;
	vv->current_hps_sync = SAA7146_HPS_SYNC_PORT_A;
}