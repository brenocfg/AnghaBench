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
typedef  enum bcm_sysport_stat_type { ____Placeholder_bcm_sysport_stat_type } bcm_sysport_stat_type ;

/* Variables and functions */
#define  BCM_SYSPORT_STAT_NETDEV 132 
#define  BCM_SYSPORT_STAT_NETDEV64 131 
#define  BCM_SYSPORT_STAT_RBUF 130 
#define  BCM_SYSPORT_STAT_RXCHK 129 
#define  BCM_SYSPORT_STAT_SOFT 128 

__attribute__((used)) static inline bool bcm_sysport_lite_stat_valid(enum bcm_sysport_stat_type type)
{
	switch (type) {
	case BCM_SYSPORT_STAT_NETDEV:
	case BCM_SYSPORT_STAT_NETDEV64:
	case BCM_SYSPORT_STAT_RXCHK:
	case BCM_SYSPORT_STAT_RBUF:
	case BCM_SYSPORT_STAT_SOFT:
		return true;
	default:
		return false;
	}
}