#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  list; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct saa7164_port {int nr; int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  read_interval; int /*<<< orphan*/  irq_svc_interval; int /*<<< orphan*/  svc_interval; int /*<<< orphan*/  irq_interval; int /*<<< orphan*/  wait_read; TYPE_4__ list_buf_free; TYPE_3__ list_buf_used; int /*<<< orphan*/  dmaqueue_lock; TYPE_2__ dmaqueue; TYPE_1__ dvb; int /*<<< orphan*/  workenc; int /*<<< orphan*/  type; struct saa7164_dev* dev; } ;
struct saa7164_dev {struct saa7164_port* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SAA7164_MAX_PORTS ; 
 int /*<<< orphan*/  SAA7164_MPEG_DVB ; 
 int /*<<< orphan*/  SAA7164_MPEG_ENCODER ; 
 int /*<<< orphan*/  SAA7164_MPEG_VBI ; 
 int SAA7164_PORT_ENC1 ; 
 int SAA7164_PORT_ENC2 ; 
 int SAA7164_PORT_TS1 ; 
 int SAA7164_PORT_TS2 ; 
 int SAA7164_PORT_VBI1 ; 
 int SAA7164_PORT_VBI2 ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7164_histogram_reset (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  saa7164_work_enchandler ; 
 int /*<<< orphan*/  saa7164_work_vbihandler ; 

__attribute__((used)) static int saa7164_port_init(struct saa7164_dev *dev, int portnr)
{
	struct saa7164_port *port = NULL;

	if ((portnr < 0) || (portnr >= SAA7164_MAX_PORTS))
		BUG();

	port = &dev->ports[portnr];

	port->dev = dev;
	port->nr = portnr;

	if ((portnr == SAA7164_PORT_TS1) || (portnr == SAA7164_PORT_TS2))
		port->type = SAA7164_MPEG_DVB;
	else
	if ((portnr == SAA7164_PORT_ENC1) || (portnr == SAA7164_PORT_ENC2)) {
		port->type = SAA7164_MPEG_ENCODER;

		/* We need a deferred interrupt handler for cmd handling */
		INIT_WORK(&port->workenc, saa7164_work_enchandler);
	} else if ((portnr == SAA7164_PORT_VBI1) || (portnr == SAA7164_PORT_VBI2)) {
		port->type = SAA7164_MPEG_VBI;

		/* We need a deferred interrupt handler for cmd handling */
		INIT_WORK(&port->workenc, saa7164_work_vbihandler);
	} else
		BUG();

	/* Init all the critical resources */
	mutex_init(&port->dvb.lock);
	INIT_LIST_HEAD(&port->dmaqueue.list);
	mutex_init(&port->dmaqueue_lock);

	INIT_LIST_HEAD(&port->list_buf_used.list);
	INIT_LIST_HEAD(&port->list_buf_free.list);
	init_waitqueue_head(&port->wait_read);


	saa7164_histogram_reset(&port->irq_interval, "irq intervals");
	saa7164_histogram_reset(&port->svc_interval, "deferred intervals");
	saa7164_histogram_reset(&port->irq_svc_interval,
		"irq to deferred intervals");
	saa7164_histogram_reset(&port->read_interval,
		"encoder/vbi read() intervals");
	saa7164_histogram_reset(&port->poll_interval,
		"encoder/vbi poll() intervals");

	return 0;
}