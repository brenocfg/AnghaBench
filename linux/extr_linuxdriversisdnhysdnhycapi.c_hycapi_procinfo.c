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
typedef  TYPE_2__ hycapictrl_info ;
struct TYPE_3__ {int iobase; int irq; } ;

/* Variables and functions */
 size_t VER_DRIVER ; 
 char* hycapi_revision ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int,int,char*) ; 

__attribute__((used)) static char *hycapi_procinfo(struct capi_ctr *ctrl)
{
	hycapictrl_info *cinfo = (hycapictrl_info *)(ctrl->driverdata);
#ifdef HYCAPI_PRINTFNAMES
	printk(KERN_NOTICE "%s\n", __func__);
#endif
	if (!cinfo)
		return "";
	sprintf(cinfo->infobuf, "%s %s 0x%x %d %s",
		cinfo->cardname[0] ? cinfo->cardname : "-",
		cinfo->version[VER_DRIVER] ? cinfo->version[VER_DRIVER] : "-",
		cinfo->card ? cinfo->card->iobase : 0x0,
		cinfo->card ? cinfo->card->irq : 0,
		hycapi_revision
		);
	return cinfo->infobuf;
}