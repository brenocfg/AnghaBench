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
struct scsi_info_t {int manf_id; } ;
struct pcmcia_device {TYPE_1__** resource; struct scsi_info_t* priv; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int MANFID_MACNICA ; 
 int MANFID_PIONEER ; 
 int /*<<< orphan*/  SYM53C500_int_host_reset (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int sym53c500_resume(struct pcmcia_device *link)
{
	struct scsi_info_t *info = link->priv;

	/* See earlier comment about manufacturer IDs. */
	if ((info->manf_id == MANFID_MACNICA) ||
	    (info->manf_id == MANFID_PIONEER) ||
	    (info->manf_id == 0x0098)) {
		outb(0x80, link->resource[0]->start + 0xd);
		outb(0x24, link->resource[0]->start + 0x9);
		outb(0x04, link->resource[0]->start + 0xd);
	}
	/*
	 *  If things don't work after a "resume",
	 *  this is a good place to start looking.
	 */
	SYM53C500_int_host_reset(link->resource[0]->start);

	return 0;
}