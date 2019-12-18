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
typedef  int u64 ;
struct nfp_pf {int /*<<< orphan*/  cpp; int /*<<< orphan*/  rtbl; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  nfp_cppcore_pcie_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,char*) ; 
 int nfp_rtsym_read_le (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

int nfp_pf_rtsym_read_optional(struct nfp_pf *pf, const char *format,
			       unsigned int default_val)
{
	char name[256];
	int err = 0;
	u64 val;

	snprintf(name, sizeof(name), format, nfp_cppcore_pcie_unit(pf->cpp));

	val = nfp_rtsym_read_le(pf->rtbl, name, &err);
	if (err) {
		if (err == -ENOENT)
			return default_val;
		nfp_err(pf->cpp, "Unable to read symbol %s\n", name);
		return err;
	}

	return val;
}