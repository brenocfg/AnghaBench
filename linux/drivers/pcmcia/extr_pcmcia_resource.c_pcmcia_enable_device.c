#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  unsigned char u16 ;
struct TYPE_15__ {int flags; scalar_t__ io_irq; int /*<<< orphan*/  Vpp; } ;
struct pcmcia_socket {int state; int functions; int /*<<< orphan*/  ops_mutex; TYPE_2__* io; TYPE_3__* ops; int /*<<< orphan*/  lock_count; TYPE_7__ socket; scalar_t__ pcmcia_irq; } ;
struct pcmcia_device {unsigned int config_flags; int config_regs; unsigned int config_base; unsigned char config_index; int _locked; int /*<<< orphan*/  dev; int /*<<< orphan*/  vpp; scalar_t__ _io; TYPE_5__* function_config; struct pcmcia_socket* socket; } ;
struct TYPE_13__ {int map; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; int /*<<< orphan*/  speed; } ;
typedef  TYPE_4__ pccard_io_map ;
struct TYPE_14__ {int state; TYPE_9__* io; } ;
typedef  TYPE_5__ config_t ;
struct TYPE_16__ {int start; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_io_map ) (struct pcmcia_socket*,TYPE_4__*) ;scalar_t__ (* set_socket ) (struct pcmcia_socket*,TYPE_7__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  Config; TYPE_1__* res; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 unsigned char CCSR_AUDIO_ENA ; 
 unsigned int CISREG_CCSR ; 
 unsigned int CISREG_COR ; 
 unsigned int CISREG_ESR ; 
 unsigned int CISREG_IOBASE_0 ; 
 unsigned int CISREG_IOBASE_1 ; 
 unsigned int CISREG_IOSIZE ; 
 unsigned int CISREG_PRR ; 
 unsigned int CISREG_SCR ; 
 int CONFIG_IO_REQ ; 
 int CONFIG_LOCKED ; 
 unsigned int CONF_ENABLE_ESR ; 
 unsigned int CONF_ENABLE_IOCARD ; 
 unsigned int CONF_ENABLE_IRQ ; 
 unsigned int CONF_ENABLE_PULSE_IRQ ; 
 unsigned int CONF_ENABLE_SPKR ; 
 unsigned int CONF_ENABLE_ZVCARD ; 
 unsigned char COR_ADDR_DECODE ; 
 unsigned char COR_CONFIG_MASK ; 
 unsigned char COR_FUNC_ENA ; 
 unsigned char COR_IREQ_ENA ; 
 unsigned char COR_LEVEL_REQ ; 
 unsigned char COR_MFC_CONFIG_MASK ; 
 int EACCES ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned char ESR_REQ_ATTN_ENA ; 
 int IO_DATA_PATH_WIDTH ; 
#define  IO_DATA_PATH_WIDTH_16 129 
#define  IO_DATA_PATH_WIDTH_AUTO 128 
 int /*<<< orphan*/  MAP_16BIT ; 
 int /*<<< orphan*/  MAP_ACTIVE ; 
 int /*<<< orphan*/  MAP_AUTOSZ ; 
 int MAX_IO_WIN ; 
 int PRESENT_COPY ; 
 int PRESENT_EXT_STATUS ; 
 int PRESENT_IOBASE_0 ; 
 int PRESENT_IOSIZE ; 
 int PRESENT_OPTION ; 
 int PRESENT_PIN_REPLACE ; 
 int PRESENT_STATUS ; 
 int SOCKET_PRESENT ; 
 int SS_IOCARD ; 
 int SS_SPKR_ENA ; 
 int SS_ZVCARD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  io_speed ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_write_cis_mem (struct pcmcia_socket*,int,unsigned int,int,unsigned char*) ; 
 unsigned char resource_size (TYPE_9__*) ; 
 scalar_t__ stub1 (struct pcmcia_socket*,TYPE_7__*) ; 
 scalar_t__ stub2 (struct pcmcia_socket*,TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (struct pcmcia_socket*,TYPE_4__*) ; 

int pcmcia_enable_device(struct pcmcia_device *p_dev)
{
	int i;
	unsigned int base;
	struct pcmcia_socket *s = p_dev->socket;
	config_t *c;
	pccard_io_map iomap;
	unsigned char status = 0;
	unsigned char ext_status = 0;
	unsigned char option = 0;
	unsigned int flags = p_dev->config_flags;

	if (!(s->state & SOCKET_PRESENT))
		return -ENODEV;

	mutex_lock(&s->ops_mutex);
	c = p_dev->function_config;
	if (c->state & CONFIG_LOCKED) {
		mutex_unlock(&s->ops_mutex);
		dev_dbg(&p_dev->dev, "Configuration is locked\n");
		return -EACCES;
	}

	/* Do power control.  We don't allow changes in Vcc. */
	s->socket.Vpp = p_dev->vpp;
	if (s->ops->set_socket(s, &s->socket)) {
		mutex_unlock(&s->ops_mutex);
		dev_warn(&p_dev->dev, "Unable to set socket state\n");
		return -EINVAL;
	}

	/* Pick memory or I/O card, DMA mode, interrupt */
	if (p_dev->_io || flags & CONF_ENABLE_IRQ)
		flags |= CONF_ENABLE_IOCARD;
	if (flags & CONF_ENABLE_IOCARD)
		s->socket.flags |= SS_IOCARD;
	if (flags & CONF_ENABLE_ZVCARD)
		s->socket.flags |= SS_ZVCARD | SS_IOCARD;
	if (flags & CONF_ENABLE_SPKR) {
		s->socket.flags |= SS_SPKR_ENA;
		status = CCSR_AUDIO_ENA;
		if (!(p_dev->config_regs & PRESENT_STATUS))
			dev_warn(&p_dev->dev, "speaker requested, but "
					      "PRESENT_STATUS not set!\n");
	}
	if (flags & CONF_ENABLE_IRQ)
		s->socket.io_irq = s->pcmcia_irq;
	else
		s->socket.io_irq = 0;
	if (flags & CONF_ENABLE_ESR) {
		p_dev->config_regs |= PRESENT_EXT_STATUS;
		ext_status = ESR_REQ_ATTN_ENA;
	}
	s->ops->set_socket(s, &s->socket);
	s->lock_count++;

	dev_dbg(&p_dev->dev,
		"enable_device: V %d, flags %x, base %x, regs %x, idx %x\n",
		p_dev->vpp, flags, p_dev->config_base, p_dev->config_regs,
		p_dev->config_index);

	/* Set up CIS configuration registers */
	base = p_dev->config_base;
	if (p_dev->config_regs & PRESENT_COPY) {
		u16 tmp = 0;
		dev_dbg(&p_dev->dev, "clearing CISREG_SCR\n");
		pcmcia_write_cis_mem(s, 1, (base + CISREG_SCR)>>1, 1, &tmp);
	}
	if (p_dev->config_regs & PRESENT_PIN_REPLACE) {
		u16 tmp = 0;
		dev_dbg(&p_dev->dev, "clearing CISREG_PRR\n");
		pcmcia_write_cis_mem(s, 1, (base + CISREG_PRR)>>1, 1, &tmp);
	}
	if (p_dev->config_regs & PRESENT_OPTION) {
		if (s->functions == 1) {
			option = p_dev->config_index & COR_CONFIG_MASK;
		} else {
			option = p_dev->config_index & COR_MFC_CONFIG_MASK;
			option |= COR_FUNC_ENA|COR_IREQ_ENA;
			if (p_dev->config_regs & PRESENT_IOBASE_0)
				option |= COR_ADDR_DECODE;
		}
		if ((flags & CONF_ENABLE_IRQ) &&
			!(flags & CONF_ENABLE_PULSE_IRQ))
			option |= COR_LEVEL_REQ;
		pcmcia_write_cis_mem(s, 1, (base + CISREG_COR)>>1, 1, &option);
		msleep(40);
	}
	if (p_dev->config_regs & PRESENT_STATUS)
		pcmcia_write_cis_mem(s, 1, (base + CISREG_CCSR)>>1, 1, &status);

	if (p_dev->config_regs & PRESENT_EXT_STATUS)
		pcmcia_write_cis_mem(s, 1, (base + CISREG_ESR)>>1, 1,
					&ext_status);

	if (p_dev->config_regs & PRESENT_IOBASE_0) {
		u8 b = c->io[0].start & 0xff;
		pcmcia_write_cis_mem(s, 1, (base + CISREG_IOBASE_0)>>1, 1, &b);
		b = (c->io[0].start >> 8) & 0xff;
		pcmcia_write_cis_mem(s, 1, (base + CISREG_IOBASE_1)>>1, 1, &b);
	}
	if (p_dev->config_regs & PRESENT_IOSIZE) {
		u8 b = resource_size(&c->io[0]) + resource_size(&c->io[1]) - 1;
		pcmcia_write_cis_mem(s, 1, (base + CISREG_IOSIZE)>>1, 1, &b);
	}

	/* Configure I/O windows */
	if (c->state & CONFIG_IO_REQ) {
		iomap.speed = io_speed;
		for (i = 0; i < MAX_IO_WIN; i++)
			if (s->io[i].res) {
				iomap.map = i;
				iomap.flags = MAP_ACTIVE;
				switch (s->io[i].res->flags & IO_DATA_PATH_WIDTH) {
				case IO_DATA_PATH_WIDTH_16:
					iomap.flags |= MAP_16BIT; break;
				case IO_DATA_PATH_WIDTH_AUTO:
					iomap.flags |= MAP_AUTOSZ; break;
				default:
					break;
				}
				iomap.start = s->io[i].res->start;
				iomap.stop = s->io[i].res->end;
				s->ops->set_io_map(s, &iomap);
				s->io[i].Config++;
			}
	}

	c->state |= CONFIG_LOCKED;
	p_dev->_locked = 1;
	mutex_unlock(&s->ops_mutex);
	return 0;
}