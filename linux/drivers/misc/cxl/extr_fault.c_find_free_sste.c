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
struct cxl_sste {int /*<<< orphan*/  esid_data; } ;
struct cxl_context {int sst_size; int sst_lru; struct cxl_sste* sstp; } ;
struct copro_slb {int vsid; unsigned int esid; } ;

/* Variables and functions */
 unsigned int SID_SHIFT ; 
 unsigned int SID_SHIFT_1T ; 
 int SLB_ESID_V ; 
 int SLB_VSID_B_1T ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ sste_matches (struct cxl_sste*,struct copro_slb*) ; 

__attribute__((used)) static struct cxl_sste *find_free_sste(struct cxl_context *ctx,
				       struct copro_slb *slb)
{
	struct cxl_sste *primary, *sste, *ret = NULL;
	unsigned int mask = (ctx->sst_size >> 7) - 1; /* SSTP0[SegTableSize] */
	unsigned int entry;
	unsigned int hash;

	if (slb->vsid & SLB_VSID_B_1T)
		hash = (slb->esid >> SID_SHIFT_1T) & mask;
	else /* 256M */
		hash = (slb->esid >> SID_SHIFT) & mask;

	primary = ctx->sstp + (hash << 3);

	for (entry = 0, sste = primary; entry < 8; entry++, sste++) {
		if (!ret && !(be64_to_cpu(sste->esid_data) & SLB_ESID_V))
			ret = sste;
		if (sste_matches(sste, slb))
			return NULL;
	}
	if (ret)
		return ret;

	/* Nothing free, select an entry to cast out */
	ret = primary + ctx->sst_lru;
	ctx->sst_lru = (ctx->sst_lru + 1) & 0x7;

	return ret;
}