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
typedef  int /*<<< orphan*/  u32 ;
struct vxlanhdr_gpe {int np_applied; int /*<<< orphan*/  next_protocol; } ;
struct vxlanhdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EPFNOSUPPORT ; 
 int /*<<< orphan*/  tun_p_from_eth_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_build_gpe_hdr(struct vxlanhdr *vxh, u32 vxflags,
			       __be16 protocol)
{
	struct vxlanhdr_gpe *gpe = (struct vxlanhdr_gpe *)vxh;

	gpe->np_applied = 1;
	gpe->next_protocol = tun_p_from_eth_p(protocol);
	if (!gpe->next_protocol)
		return -EPFNOSUPPORT;
	return 0;
}