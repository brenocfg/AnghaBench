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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int TCA_CSUM_UPDATE_FLAG_TCP ; 
 int TCA_CSUM_UPDATE_FLAG_UDP ; 

__attribute__((used)) static u32 nfp_fl_csum_l4_to_flag(u8 ip_proto)
{
	switch (ip_proto) {
	case 0:
		/* Filter doesn't force proto match,
		 * both TCP and UDP will be updated if encountered
		 */
		return TCA_CSUM_UPDATE_FLAG_TCP | TCA_CSUM_UPDATE_FLAG_UDP;
	case IPPROTO_TCP:
		return TCA_CSUM_UPDATE_FLAG_TCP;
	case IPPROTO_UDP:
		return TCA_CSUM_UPDATE_FLAG_UDP;
	default:
		/* All other protocols will be ignored by FW */
		return 0;
	}
}