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
struct nfp_nffw_info_data {int dummy; } ;
struct nfp_nffw_info {int /*<<< orphan*/  res; struct nfp_cpp* cpp; struct nfp_nffw_info_data fwinf; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nfp_nffw_info* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NFFW_INFO_VERSION_CURRENT ; 
 int /*<<< orphan*/  NFP_RESOURCE_NFP_NFFW ; 
 int /*<<< orphan*/  kfree (struct nfp_nffw_info*) ; 
 struct nfp_nffw_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nffw_res_flg_init_get (struct nfp_nffw_info_data*) ; 
 scalar_t__ nffw_res_info_version_get (struct nfp_nffw_info_data*) ; 
 int nfp_cpp_read (struct nfp_cpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_nffw_info_data*,int) ; 
 int /*<<< orphan*/  nfp_resource_acquire (struct nfp_cpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_resource_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_resource_cpp_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_resource_release (int /*<<< orphan*/ ) ; 
 int nfp_resource_size (int /*<<< orphan*/ ) ; 

struct nfp_nffw_info *nfp_nffw_info_open(struct nfp_cpp *cpp)
{
	struct nfp_nffw_info_data *fwinf;
	struct nfp_nffw_info *state;
	u32 info_ver;
	int err;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return ERR_PTR(-ENOMEM);

	state->res = nfp_resource_acquire(cpp, NFP_RESOURCE_NFP_NFFW);
	if (IS_ERR(state->res))
		goto err_free;

	fwinf = &state->fwinf;

	if (sizeof(*fwinf) > nfp_resource_size(state->res))
		goto err_release;

	err = nfp_cpp_read(cpp, nfp_resource_cpp_id(state->res),
			   nfp_resource_address(state->res),
			   fwinf, sizeof(*fwinf));
	if (err < (int)sizeof(*fwinf))
		goto err_release;

	if (!nffw_res_flg_init_get(fwinf))
		goto err_release;

	info_ver = nffw_res_info_version_get(fwinf);
	if (info_ver > NFFW_INFO_VERSION_CURRENT)
		goto err_release;

	state->cpp = cpp;
	return state;

err_release:
	nfp_resource_release(state->res);
err_free:
	kfree(state);
	return ERR_PTR(-EIO);
}