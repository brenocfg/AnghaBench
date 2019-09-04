#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {struct qed_bulletin_content* p_virt; } ;
struct qed_vf_info {TYPE_1__ bulletin; } ;
struct qed_mcp_link_state {int dummy; } ;
struct qed_mcp_link_params {int dummy; } ;
struct qed_mcp_link_capabilities {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_bulletin_content {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qed_vf_get_link_caps (struct qed_hwfn*,struct qed_mcp_link_capabilities*,struct qed_bulletin_content*) ; 
 int /*<<< orphan*/  __qed_vf_get_link_params (struct qed_hwfn*,struct qed_mcp_link_params*,struct qed_bulletin_content*) ; 
 int /*<<< orphan*/  __qed_vf_get_link_state (struct qed_hwfn*,struct qed_mcp_link_state*,struct qed_bulletin_content*) ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qed_iov_get_link(struct qed_hwfn *p_hwfn,
			     u16 vfid,
			     struct qed_mcp_link_params *p_params,
			     struct qed_mcp_link_state *p_link,
			     struct qed_mcp_link_capabilities *p_caps)
{
	struct qed_vf_info *p_vf = qed_iov_get_vf_info(p_hwfn,
						       vfid,
						       false);
	struct qed_bulletin_content *p_bulletin;

	if (!p_vf)
		return;

	p_bulletin = p_vf->bulletin.p_virt;

	if (p_params)
		__qed_vf_get_link_params(p_hwfn, p_params, p_bulletin);
	if (p_link)
		__qed_vf_get_link_state(p_hwfn, p_link, p_bulletin);
	if (p_caps)
		__qed_vf_get_link_caps(p_hwfn, p_caps, p_bulletin);
}