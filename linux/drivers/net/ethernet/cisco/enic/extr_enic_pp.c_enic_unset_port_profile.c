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
struct enic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENIC_DEVCMD_PROXY_BY_INDEX (int,int,struct enic*,int /*<<< orphan*/ ) ; 
 int PORT_SELF_VF ; 
 int enic_dev_status_to_errno (int) ; 
 int /*<<< orphan*/  enic_reset_addr_lists (struct enic*) ; 
 int /*<<< orphan*/  vnic_dev_deinit ; 

__attribute__((used)) static int enic_unset_port_profile(struct enic *enic, int vf)
{
	int err;

	ENIC_DEVCMD_PROXY_BY_INDEX(vf, err, enic, vnic_dev_deinit);
	if (err)
		return enic_dev_status_to_errno(err);

	if (vf == PORT_SELF_VF)
		enic_reset_addr_lists(enic);

	return 0;
}