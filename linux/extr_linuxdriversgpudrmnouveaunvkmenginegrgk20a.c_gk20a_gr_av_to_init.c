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
struct gk20a_fw_av {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct gf100_gr_pack {struct gf100_gr_init* init; } ;
struct gf100_gr_init {int count; int pitch; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct gf100_gr_fuc {int size; scalar_t__ data; } ;
struct gf100_gr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int gf100_gr_ctor_fw (struct gf100_gr*,char const*,struct gf100_gr_fuc*) ; 
 int /*<<< orphan*/  gf100_gr_dtor_fw (struct gf100_gr_fuc*) ; 
 struct gf100_gr_pack* vzalloc (int) ; 

int
gk20a_gr_av_to_init(struct gf100_gr *gr, const char *fw_name,
		    struct gf100_gr_pack **ppack)
{
	struct gf100_gr_fuc fuc;
	struct gf100_gr_init *init;
	struct gf100_gr_pack *pack;
	int nent;
	int ret;
	int i;

	ret = gf100_gr_ctor_fw(gr, fw_name, &fuc);
	if (ret)
		return ret;

	nent = (fuc.size / sizeof(struct gk20a_fw_av));
	pack = vzalloc((sizeof(*pack) * 2) + (sizeof(*init) * (nent + 1)));
	if (!pack) {
		ret = -ENOMEM;
		goto end;
	}

	init = (void *)(pack + 2);
	pack[0].init = init;

	for (i = 0; i < nent; i++) {
		struct gf100_gr_init *ent = &init[i];
		struct gk20a_fw_av *av = &((struct gk20a_fw_av *)fuc.data)[i];

		ent->addr = av->addr;
		ent->data = av->data;
		ent->count = 1;
		ent->pitch = 1;
	}

	*ppack = pack;

end:
	gf100_gr_dtor_fw(&fuc);
	return ret;
}