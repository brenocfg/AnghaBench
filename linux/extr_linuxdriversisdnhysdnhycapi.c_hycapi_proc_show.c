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
struct seq_file {struct capi_ctr* private; } ;
struct capi_ctr {scalar_t__ driverdata; } ;
struct TYPE_3__ {char* iobase; char* irq; int brdtype; } ;
typedef  TYPE_1__ hysdn_card ;
struct TYPE_4__ {char* cardname; char** version; TYPE_1__* card; } ;
typedef  TYPE_2__ hycapictrl_info ;

/* Variables and functions */
#define  BD_CHAMP2 132 
#define  BD_ERGO 131 
#define  BD_METRO 130 
#define  BD_PCCARD 129 
#define  BD_PLEXUS 128 
 size_t VER_CARDTYPE ; 
 size_t VER_DRIVER ; 
 size_t VER_SERIAL ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*) ; 

__attribute__((used)) static int hycapi_proc_show(struct seq_file *m, void *v)
{
	struct capi_ctr *ctrl = m->private;
	hycapictrl_info *cinfo = (hycapictrl_info *)(ctrl->driverdata);
	hysdn_card *card = cinfo->card;
	char *s;

	seq_printf(m, "%-16s %s\n", "name", cinfo->cardname);
	seq_printf(m, "%-16s 0x%x\n", "io", card->iobase);
	seq_printf(m, "%-16s %d\n", "irq", card->irq);

	switch (card->brdtype) {
	case BD_PCCARD:  s = "HYSDN Hycard"; break;
	case BD_ERGO: s = "HYSDN Ergo2"; break;
	case BD_METRO: s = "HYSDN Metro4"; break;
	case BD_CHAMP2: s = "HYSDN Champ2";	break;
	case BD_PLEXUS: s = "HYSDN Plexus30"; break;
	default: s = "???"; break;
	}
	seq_printf(m, "%-16s %s\n", "type", s);
	if ((s = cinfo->version[VER_DRIVER]) != NULL)
		seq_printf(m, "%-16s %s\n", "ver_driver", s);
	if ((s = cinfo->version[VER_CARDTYPE]) != NULL)
		seq_printf(m, "%-16s %s\n", "ver_cardtype", s);
	if ((s = cinfo->version[VER_SERIAL]) != NULL)
		seq_printf(m, "%-16s %s\n", "ver_serial", s);

	seq_printf(m, "%-16s %s\n", "cardname", cinfo->cardname);

	return 0;
}