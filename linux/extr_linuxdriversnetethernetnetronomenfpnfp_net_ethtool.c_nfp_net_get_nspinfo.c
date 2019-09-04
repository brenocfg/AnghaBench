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
struct nfp_nsp {int dummy; } ;
struct nfp_app {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_FWVERS_LEN ; 
 scalar_t__ IS_ERR (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_close (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_get_abi_ver_major (struct nfp_nsp*) ; 
 int /*<<< orphan*/  nfp_nsp_get_abi_ver_minor (struct nfp_nsp*) ; 
 struct nfp_nsp* nfp_nsp_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_get_nspinfo(struct nfp_app *app, char *version)
{
	struct nfp_nsp *nsp;

	if (!app)
		return;

	nsp = nfp_nsp_open(app->cpp);
	if (IS_ERR(nsp))
		return;

	snprintf(version, ETHTOOL_FWVERS_LEN, "%hu.%hu",
		 nfp_nsp_get_abi_ver_major(nsp),
		 nfp_nsp_get_abi_ver_minor(nsp));

	nfp_nsp_close(nsp);
}