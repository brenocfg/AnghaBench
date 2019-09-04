#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct gk20a_fw_av {int addr; int /*<<< orphan*/  data; } ;
struct gf100_gr_pack {scalar_t__ type; struct gf100_gr_init* init; } ;
struct gf100_gr_init {int count; int pitch; int /*<<< orphan*/  data; scalar_t__ addr; } ;
struct gf100_gr_fuc {int size; scalar_t__ data; } ;
struct gf100_gr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int gf100_gr_ctor_fw (struct gf100_gr*,char const*,struct gf100_gr_fuc*) ; 
 int /*<<< orphan*/  gf100_gr_dtor_fw (struct gf100_gr_fuc*) ; 
 int /*<<< orphan*/  vfree (struct gf100_gr_pack*) ; 
 struct gf100_gr_pack* vzalloc (int) ; 

int
gk20a_gr_av_to_method(struct gf100_gr *gr, const char *fw_name,
		      struct gf100_gr_pack **ppack)
{
	struct gf100_gr_fuc fuc;
	struct gf100_gr_init *init;
	struct gf100_gr_pack *pack;
	/* We don't suppose we will initialize more than 16 classes here... */
	static const unsigned int max_classes = 16;
	u32 classidx = 0, prevclass = 0;
	int nent;
	int ret;
	int i;

	ret = gf100_gr_ctor_fw(gr, fw_name, &fuc);
	if (ret)
		return ret;

	nent = (fuc.size / sizeof(struct gk20a_fw_av));

	pack = vzalloc((sizeof(*pack) * max_classes) +
		       (sizeof(*init) * (nent + 1)));
	if (!pack) {
		ret = -ENOMEM;
		goto end;
	}

	init = (void *)(pack + max_classes);

	for (i = 0; i < nent; i++) {
		struct gf100_gr_init *ent = &init[i];
		struct gk20a_fw_av *av = &((struct gk20a_fw_av *)fuc.data)[i];
		u32 class = av->addr & 0xffff;
		u32 addr = (av->addr & 0xffff0000) >> 14;

		if (prevclass != class) {
			pack[classidx].init = ent;
			pack[classidx].type = class;
			prevclass = class;
			if (++classidx >= max_classes) {
				vfree(pack);
				ret = -ENOSPC;
				goto end;
			}
		}

		ent->addr = addr;
		ent->data = av->data;
		ent->count = 1;
		ent->pitch = 1;
	}

	*ppack = pack;

end:
	gf100_gr_dtor_fw(&fuc);
	return ret;
}