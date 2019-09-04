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
struct capi_ctr {scalar_t__ driverdata; } ;
struct TYPE_4__ {char* infobuf; char* cardname; char** version; TYPE_1__* card; } ;
typedef  TYPE_2__ avmctrl_info ;
struct TYPE_3__ {int port; int irq; int revision; } ;

/* Variables and functions */
 size_t VER_DRIVER ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int,int,int) ; 

__attribute__((used)) static char *b1pcmcia_procinfo(struct capi_ctr *ctrl)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);

	if (!cinfo)
		return "";
	sprintf(cinfo->infobuf, "%s %s 0x%x %d r%d",
		cinfo->cardname[0] ? cinfo->cardname : "-",
		cinfo->version[VER_DRIVER] ? cinfo->version[VER_DRIVER] : "-",
		cinfo->card ? cinfo->card->port : 0x0,
		cinfo->card ? cinfo->card->irq : 0,
		cinfo->card ? cinfo->card->revision : 0
		);
	return cinfo->infobuf;
}