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
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IFLA_OFFLOAD_XSTATS_CPU_HIT 128 
 int nfp_repr_get_host_stats64 (struct net_device const*,void*) ; 

__attribute__((used)) static int
nfp_repr_get_offload_stats(int attr_id, const struct net_device *dev,
			   void *stats)
{
	switch (attr_id) {
	case IFLA_OFFLOAD_XSTATS_CPU_HIT:
		return nfp_repr_get_host_stats64(dev, stats);
	}

	return -EINVAL;
}