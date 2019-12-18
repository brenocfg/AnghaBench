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
typedef  int u16 ;

/* Variables and functions */
 int NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT ; 

__attribute__((used)) static bool nfp_tunnel_is_mac_idx_global(u16 nfp_mac_idx)
{
	return (nfp_mac_idx & 0xff) == NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT;
}