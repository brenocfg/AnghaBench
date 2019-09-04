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
struct nfp_nffw_info {int /*<<< orphan*/  fwinf; } ;
struct nffw_fwinfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ nffw_fwinfo_loaded_get (struct nffw_fwinfo*) ; 
 unsigned int nffw_res_fwinfos (int /*<<< orphan*/ *,struct nffw_fwinfo**) ; 

__attribute__((used)) static struct nffw_fwinfo *nfp_nffw_info_fwid_first(struct nfp_nffw_info *state)
{
	struct nffw_fwinfo *fwinfo;
	unsigned int cnt, i;

	cnt = nffw_res_fwinfos(&state->fwinf, &fwinfo);
	if (!cnt)
		return NULL;

	for (i = 0; i < cnt; i++)
		if (nffw_fwinfo_loaded_get(&fwinfo[i]))
			return &fwinfo[i];

	return NULL;
}