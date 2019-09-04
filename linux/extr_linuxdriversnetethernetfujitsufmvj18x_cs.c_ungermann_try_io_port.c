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
struct pcmcia_device {int config_index; TYPE_1__** resource; } ;
struct TYPE_2__ {unsigned int start; } ;

/* Variables and functions */
 int pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int ungermann_try_io_port(struct pcmcia_device *link)
{
    int ret;
    unsigned int ioaddr;
    /*
	Ungermann-Bass Access/CARD accepts 0x300,0x320,0x340,0x360
	0x380,0x3c0 only for ioport.
    */
    for (ioaddr = 0x300; ioaddr < 0x3e0; ioaddr += 0x20) {
	link->resource[0]->start = ioaddr;
	ret = pcmcia_request_io(link);
	if (ret == 0) {
	    /* calculate ConfigIndex value */
	    link->config_index =
		((link->resource[0]->start & 0x0f0) >> 3) | 0x22;
	    return ret;
	}
    }
    return ret;	/* RequestIO failed */
}