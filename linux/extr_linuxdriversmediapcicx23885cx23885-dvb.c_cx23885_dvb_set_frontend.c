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
struct dtv_frontend_properties {int /*<<< orphan*/  modulation; } ;
struct dvb_frontend {TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
struct cx23885_tsport {int (* set_frontend ) (struct dvb_frontend*) ;struct cx23885_dev* dev; } ;
struct cx23885_dev {int board; } ;
struct TYPE_2__ {struct cx23885_tsport* priv; } ;

/* Variables and functions */
#define  CX23885_BOARD_HAUPPAUGE_HVR1275 134 
#define  CX23885_BOARD_MAGICPRO_PROHDTVE2 133 
#define  CX23885_BOARD_MYGICA_X8506 132 
#define  CX23885_BOARD_MYGICA_X8507 131 
 int /*<<< orphan*/  GPIO_0 ; 
 int /*<<< orphan*/  GPIO_5 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  cx23885_gpio_clear (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_gpio_set (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int cx23885_dvb_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct cx23885_tsport *port = fe->dvb->priv;
	struct cx23885_dev *dev = port->dev;

	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1275:
		switch (p->modulation) {
		case VSB_8:
			cx23885_gpio_clear(dev, GPIO_5);
			break;
		case QAM_64:
		case QAM_256:
		default:
			cx23885_gpio_set(dev, GPIO_5);
			break;
		}
		break;
	case CX23885_BOARD_MYGICA_X8506:
	case CX23885_BOARD_MYGICA_X8507:
	case CX23885_BOARD_MAGICPRO_PROHDTVE2:
		/* Select Digital TV */
		cx23885_gpio_set(dev, GPIO_0);
		break;
	}

	/* Call the real set_frontend */
	if (port->set_frontend)
		return port->set_frontend(fe);

	return 0;
}