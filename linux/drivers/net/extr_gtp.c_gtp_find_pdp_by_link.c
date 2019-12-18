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
struct pdp_ctx {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct gtp_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct pdp_ctx* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t GTPA_I_TEI ; 
 size_t GTPA_MS_ADDRESS ; 
 size_t GTPA_TID ; 
 size_t GTPA_VERSION ; 
 scalar_t__ GTP_V0 ; 
 scalar_t__ GTP_V1 ; 
 struct pdp_ctx* gtp0_pdp_find (struct gtp_dev*,int /*<<< orphan*/ ) ; 
 struct pdp_ctx* gtp1_pdp_find (struct gtp_dev*,scalar_t__) ; 
 struct gtp_dev* gtp_find_dev (struct net*,struct nlattr**) ; 
 struct pdp_ctx* ipv4_pdp_find (struct gtp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u64 (struct nlattr*) ; 

__attribute__((used)) static struct pdp_ctx *gtp_find_pdp_by_link(struct net *net,
					    struct nlattr *nla[])
{
	struct gtp_dev *gtp;

	gtp = gtp_find_dev(net, nla);
	if (!gtp)
		return ERR_PTR(-ENODEV);

	if (nla[GTPA_MS_ADDRESS]) {
		__be32 ip = nla_get_be32(nla[GTPA_MS_ADDRESS]);

		return ipv4_pdp_find(gtp, ip);
	} else if (nla[GTPA_VERSION]) {
		u32 gtp_version = nla_get_u32(nla[GTPA_VERSION]);

		if (gtp_version == GTP_V0 && nla[GTPA_TID])
			return gtp0_pdp_find(gtp, nla_get_u64(nla[GTPA_TID]));
		else if (gtp_version == GTP_V1 && nla[GTPA_I_TEI])
			return gtp1_pdp_find(gtp, nla_get_u32(nla[GTPA_I_TEI]));
	}

	return ERR_PTR(-EINVAL);
}