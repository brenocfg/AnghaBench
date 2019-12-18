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
struct pcmcia_device {int config_flags; int io_lines; int config_index; TYPE_1__** resource; struct net_device* priv; } ;
struct net_device {int base_addr; } ;
struct TYPE_2__ {int end; unsigned int start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CONF_ENABLE_IRQ ; 
 int CONF_ENABLE_SPKR ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int osi_config(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    static const unsigned int com[4] = { 0x3f8, 0x2f8, 0x3e8, 0x2e8 };
    int i, j;

    link->config_flags |= CONF_ENABLE_SPKR | CONF_ENABLE_IRQ;
    link->resource[0]->end = 64;
    link->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
    link->resource[1]->end = 8;

    /* Enable Hard Decode, LAN, Modem */
    link->io_lines = 16;
    link->config_index = 0x23;

    for (i = j = 0; j < 4; j++) {
	link->resource[1]->start = com[j];
	i = pcmcia_request_io(link);
	if (i == 0)
		break;
    }
    if (i != 0) {
	/* Fallback: turn off hard decode */
	link->config_index = 0x03;
	link->resource[1]->end = 0;
	i = pcmcia_request_io(link);
    }
    dev->base_addr = link->resource[0]->start + 0x10;
    return i;
}