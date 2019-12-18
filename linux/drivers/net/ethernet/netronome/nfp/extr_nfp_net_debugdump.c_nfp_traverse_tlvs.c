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
typedef  int u32 ;
struct nfp_pf {int dummy; } ;
struct nfp_dump_tl {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
typedef  int (* nfp_tlv_visit ) (struct nfp_pf*,struct nfp_dump_tl*,void*) ;

/* Variables and functions */
 int EINVAL ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_traverse_tlvs(struct nfp_pf *pf, void *data, u32 data_length, void *param,
		  nfp_tlv_visit tlv_visit)
{
	long long remaining = data_length;
	struct nfp_dump_tl *tl;
	u32 total_tlv_size;
	void *p = data;
	int err;

	while (remaining >= sizeof(*tl)) {
		tl = p;
		if (!tl->type && !tl->length)
			break;

		if (be32_to_cpu(tl->length) > remaining - sizeof(*tl))
			return -EINVAL;

		total_tlv_size = sizeof(*tl) + be32_to_cpu(tl->length);

		/* Spec TLVs should be aligned to 4 bytes. */
		if (total_tlv_size % 4 != 0)
			return -EINVAL;

		p += total_tlv_size;
		remaining -= total_tlv_size;
		err = tlv_visit(pf, tl, param);
		if (err)
			return err;
	}

	return 0;
}