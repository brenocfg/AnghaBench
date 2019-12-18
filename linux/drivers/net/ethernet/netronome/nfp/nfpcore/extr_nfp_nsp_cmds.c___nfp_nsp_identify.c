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
struct nsp_identify {int /*<<< orphan*/  sensor_mask; int /*<<< orphan*/  nsp; int /*<<< orphan*/  secondary; int /*<<< orphan*/  primary; int /*<<< orphan*/  br_nsp; int /*<<< orphan*/  br_secondary; int /*<<< orphan*/  br_primary; int /*<<< orphan*/  flags; int /*<<< orphan*/  version; } ;
struct nfp_nsp_identify {char* version; int /*<<< orphan*/  sensor_mask; void* nsp; void* secondary; void* primary; int /*<<< orphan*/  br_nsp; int /*<<< orphan*/  br_secondary; int /*<<< orphan*/  br_primary; int /*<<< orphan*/  flags; } ;
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct nsp_identify*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nfp_nsp_cpp (struct nfp_nsp*) ; 
 int nfp_nsp_get_abi_ver_minor (struct nfp_nsp*) ; 
 int nfp_nsp_read_identify (struct nfp_nsp*,struct nsp_identify*,int) ; 

struct nfp_nsp_identify *__nfp_nsp_identify(struct nfp_nsp *nsp)
{
	struct nfp_nsp_identify *nspi = NULL;
	struct nsp_identify *ni;
	int ret;

	if (nfp_nsp_get_abi_ver_minor(nsp) < 15)
		return NULL;

	ni = kzalloc(sizeof(*ni), GFP_KERNEL);
	if (!ni)
		return NULL;

	ret = nfp_nsp_read_identify(nsp, ni, sizeof(*ni));
	if (ret < 0) {
		nfp_err(nfp_nsp_cpp(nsp), "reading bsp version failed %d\n",
			ret);
		goto exit_free;
	}

	nspi = kzalloc(sizeof(*nspi), GFP_KERNEL);
	if (!nspi)
		goto exit_free;

	memcpy(nspi->version, ni->version, sizeof(nspi->version));
	nspi->version[sizeof(nspi->version) - 1] = '\0';
	nspi->flags = ni->flags;
	nspi->br_primary = ni->br_primary;
	nspi->br_secondary = ni->br_secondary;
	nspi->br_nsp = ni->br_nsp;
	nspi->primary = le16_to_cpu(ni->primary);
	nspi->secondary = le16_to_cpu(ni->secondary);
	nspi->nsp = le16_to_cpu(ni->nsp);
	nspi->sensor_mask = le64_to_cpu(ni->sensor_mask);

exit_free:
	kfree(ni);
	return nspi;
}