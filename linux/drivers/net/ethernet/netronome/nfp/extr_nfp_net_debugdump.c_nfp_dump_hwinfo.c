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
struct nfp_pf {int /*<<< orphan*/  hwinfo; } ;
struct nfp_dump_tl {int /*<<< orphan*/  data; } ;
struct nfp_dump_state {struct nfp_dump_tl* p; } ;

/* Variables and functions */
 scalar_t__ ALIGN8 (scalar_t__) ; 
 int /*<<< orphan*/  NFP_DUMPSPEC_TYPE_HWINFO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int nfp_add_tlv (int /*<<< orphan*/ ,scalar_t__,struct nfp_dump_state*) ; 
 scalar_t__ nfp_hwinfo_get_packed_str_size (int /*<<< orphan*/ ) ; 
 char* nfp_hwinfo_get_packed_strings (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_dump_hwinfo(struct nfp_pf *pf, struct nfp_dump_tl *spec,
		struct nfp_dump_state *dump)
{
	struct nfp_dump_tl *dump_header = dump->p;
	u32 hwinfo_size, total_size;
	char *hwinfo;
	int err;

	hwinfo = nfp_hwinfo_get_packed_strings(pf->hwinfo);
	hwinfo_size = nfp_hwinfo_get_packed_str_size(pf->hwinfo);
	total_size = sizeof(*dump_header) + ALIGN8(hwinfo_size);

	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_HWINFO, total_size, dump);
	if (err)
		return err;

	memcpy(dump_header->data, hwinfo, hwinfo_size);

	return 0;
}