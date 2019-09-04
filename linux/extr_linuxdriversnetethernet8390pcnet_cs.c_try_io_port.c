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
struct pcmcia_device {int io_lines; TYPE_1__** resource; } ;
struct TYPE_2__ {int end; int start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int try_io_port(struct pcmcia_device *link)
{
    int j, ret;
    link->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
    link->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
    if (link->resource[0]->end == 32) {
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	if (link->resource[1]->end > 0) {
	    /* for master/slave multifunction cards */
	    link->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
	}
    } else {
	/* This should be two 16-port windows */
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	link->resource[1]->flags |= IO_DATA_PATH_WIDTH_16;
    }
    if (link->resource[0]->start == 0) {
	for (j = 0; j < 0x400; j += 0x20) {
	    link->resource[0]->start = j ^ 0x300;
	    link->resource[1]->start = (j ^ 0x300) + 0x10;
	    link->io_lines = 16;
	    ret = pcmcia_request_io(link);
	    if (ret == 0)
		    return ret;
	}
	return ret;
    } else {
	return pcmcia_request_io(link);
    }
}