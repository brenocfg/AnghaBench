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
typedef  int u32 ;
struct nvkm_subdev {int debug; } ;
struct nv50_disp_mthd_list {scalar_t__ addr; } ;
struct nv50_disp_chan_mthd {int addr; char* name; int /*<<< orphan*/  prev; TYPE_4__* data; } ;
struct TYPE_7__ {int user; } ;
struct nv50_disp_chan {int head; TYPE_3__ chid; struct nv50_disp_chan_mthd* mthd; struct nv50_disp* disp; } ;
struct TYPE_5__ {struct nvkm_subdev subdev; } ;
struct TYPE_6__ {TYPE_1__ engine; } ;
struct nv50_disp {TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  sname_ ;
typedef  int /*<<< orphan*/  cname_ ;
struct TYPE_8__ {int nr; char* name; struct nv50_disp_mthd_list* mthd; } ;

/* Variables and functions */
 int /*<<< orphan*/  info ; 
 int /*<<< orphan*/  nv50_disp_mthd_list (struct nv50_disp*,int,int,int /*<<< orphan*/ ,struct nv50_disp_mthd_list const*,int) ; 
 int /*<<< orphan*/  nvkm_printk_ (struct nvkm_subdev*,int,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

void
nv50_disp_chan_mthd(struct nv50_disp_chan *chan, int debug)
{
	struct nv50_disp *disp = chan->disp;
	struct nvkm_subdev *subdev = &disp->base.engine.subdev;
	const struct nv50_disp_chan_mthd *mthd = chan->mthd;
	const struct nv50_disp_mthd_list *list;
	int i, j;

	if (debug > subdev->debug)
		return;

	for (i = 0; (list = mthd->data[i].mthd) != NULL; i++) {
		u32 base = chan->head * mthd->addr;
		for (j = 0; j < mthd->data[i].nr; j++, base += list->addr) {
			const char *cname = mthd->name;
			const char *sname = "";
			char cname_[16], sname_[16];

			if (mthd->addr) {
				snprintf(cname_, sizeof(cname_), "%s %d",
					 mthd->name, chan->chid.user);
				cname = cname_;
			}

			if (mthd->data[i].nr > 1) {
				snprintf(sname_, sizeof(sname_), " - %s %d",
					 mthd->data[i].name, j);
				sname = sname_;
			}

			nvkm_printk_(subdev, debug, info, "%s%s:\n", cname, sname);
			nv50_disp_mthd_list(disp, debug, base, mthd->prev,
					    list, j);
		}
	}
}