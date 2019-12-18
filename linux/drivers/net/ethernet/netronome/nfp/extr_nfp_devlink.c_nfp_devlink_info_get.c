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
struct nfp_pf {int /*<<< orphan*/  cpp; int /*<<< orphan*/  hwinfo; } ;
struct nfp_nsp {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct devlink_info_req {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 int /*<<< orphan*/  NFP_NSP_VERSION_BUFSZ ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct nfp_nsp*) ; 
 int devlink_info_driver_name_put (struct devlink_info_req*,char*) ; 
 int devlink_info_serial_number_put (struct devlink_info_req*,char*) ; 
 struct nfp_pf* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfp_devlink_versions_get_hwinfo (struct nfp_pf*,struct devlink_info_req*) ; 
 int nfp_devlink_versions_get_nsp (struct devlink_info_req*,int,char*,int /*<<< orphan*/ ) ; 
 char* nfp_hwinfo_lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_nsp_close (struct nfp_nsp*) ; 
 scalar_t__ nfp_nsp_has_versions (struct nfp_nsp*) ; 
 struct nfp_nsp* nfp_nsp_open (int /*<<< orphan*/ ) ; 
 int nfp_nsp_versions (struct nfp_nsp*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
nfp_devlink_info_get(struct devlink *devlink, struct devlink_info_req *req,
		     struct netlink_ext_ack *extack)
{
	struct nfp_pf *pf = devlink_priv(devlink);
	const char *sn, *vendor, *part;
	struct nfp_nsp *nsp;
	char *buf = NULL;
	int err;

	err = devlink_info_driver_name_put(req, "nfp");
	if (err)
		return err;

	vendor = nfp_hwinfo_lookup(pf->hwinfo, "assembly.vendor");
	part = nfp_hwinfo_lookup(pf->hwinfo, "assembly.partno");
	sn = nfp_hwinfo_lookup(pf->hwinfo, "assembly.serial");
	if (vendor && part && sn) {
		char *buf;

		buf = kmalloc(strlen(vendor) + strlen(part) + strlen(sn) + 1,
			      GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		buf[0] = '\0';
		strcat(buf, vendor);
		strcat(buf, part);
		strcat(buf, sn);

		err = devlink_info_serial_number_put(req, buf);
		kfree(buf);
		if (err)
			return err;
	}

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_ERR(nsp)) {
		NL_SET_ERR_MSG_MOD(extack, "can't access NSP");
		return PTR_ERR(nsp);
	}

	if (nfp_nsp_has_versions(nsp)) {
		buf = kzalloc(NFP_NSP_VERSION_BUFSZ, GFP_KERNEL);
		if (!buf) {
			err = -ENOMEM;
			goto err_close_nsp;
		}

		err = nfp_nsp_versions(nsp, buf, NFP_NSP_VERSION_BUFSZ);
		if (err)
			goto err_free_buf;

		err = nfp_devlink_versions_get_nsp(req, false,
						   buf, NFP_NSP_VERSION_BUFSZ);
		if (err)
			goto err_free_buf;

		err = nfp_devlink_versions_get_nsp(req, true,
						   buf, NFP_NSP_VERSION_BUFSZ);
		if (err)
			goto err_free_buf;

		kfree(buf);
	}

	nfp_nsp_close(nsp);

	return nfp_devlink_versions_get_hwinfo(pf, req);

err_free_buf:
	kfree(buf);
err_close_nsp:
	nfp_nsp_close(nsp);
	return err;
}