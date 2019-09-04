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
struct nfp_pf {int /*<<< orphan*/  mip; } ;
struct nfp_dump_tl {int /*<<< orphan*/  data; } ;
struct nfp_dump_state {struct nfp_dump_tl* p; } ;

/* Variables and functions */
 scalar_t__ ALIGN8 (scalar_t__) ; 
 int /*<<< orphan*/  NFP_DUMPSPEC_TYPE_FWNAME ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int nfp_add_tlv (int /*<<< orphan*/ ,scalar_t__,struct nfp_dump_state*) ; 
 char* nfp_mip_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int nfp_dump_fwname(struct nfp_pf *pf, struct nfp_dump_state *dump)
{
	struct nfp_dump_tl *dump_header = dump->p;
	u32 fwname_len, total_size;
	const char *fwname;
	int err;

	fwname = nfp_mip_name(pf->mip);
	fwname_len = strlen(fwname);
	total_size = sizeof(*dump_header) + ALIGN8(fwname_len + 1);

	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_FWNAME, total_size, dump);
	if (err)
		return err;

	memcpy(dump_header->data, fwname, fwname_len);

	return 0;
}