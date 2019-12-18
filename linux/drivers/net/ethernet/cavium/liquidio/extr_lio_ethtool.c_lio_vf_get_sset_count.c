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
struct octeon_device {int num_iqs; int num_oqs; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_PRIV_FLAGS 129 
#define  ETH_SS_STATS 128 
 struct lio* GET_LIO (struct net_device*) ; 
 int lio_get_priv_flags_ss_count (struct lio*) ; 
 int /*<<< orphan*/  oct_droq_stats_strings ; 
 int /*<<< orphan*/  oct_iq_stats_strings ; 
 int /*<<< orphan*/  oct_vf_stats_strings ; 

__attribute__((used)) static int lio_vf_get_sset_count(struct net_device *netdev, int sset)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct_dev = lio->oct_dev;

	switch (sset) {
	case ETH_SS_STATS:
		return (ARRAY_SIZE(oct_vf_stats_strings) +
			ARRAY_SIZE(oct_iq_stats_strings) * oct_dev->num_iqs +
			ARRAY_SIZE(oct_droq_stats_strings) * oct_dev->num_oqs);
	case ETH_SS_PRIV_FLAGS:
		return lio_get_priv_flags_ss_count(lio);
	default:
		return -EOPNOTSUPP;
	}
}