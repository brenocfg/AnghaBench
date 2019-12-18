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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int iq; int oq; } ;
struct octeon_device {TYPE_1__ io_qmask; } ;
struct net_device {int dummy; } ;
struct lio {int /*<<< orphan*/  netdev; struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_PRIV_FLAGS 129 
#define  ETH_SS_STATS 128 
 struct lio* GET_LIO (struct net_device*) ; 
 int MAX_OCTEON_INSTR_QUEUES (struct octeon_device*) ; 
 int MAX_OCTEON_OUTPUT_QUEUES (struct octeon_device*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  lio_get_priv_flags_strings (struct lio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char** oct_droq_stats_strings ; 
 char** oct_iq_stats_strings ; 
 char** oct_stats_strings ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void lio_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct_dev = lio->oct_dev;
	int num_iq_stats, num_oq_stats, i, j;
	int num_stats;

	switch (stringset) {
	case ETH_SS_STATS:
		num_stats = ARRAY_SIZE(oct_stats_strings);
		for (j = 0; j < num_stats; j++) {
			sprintf(data, "%s", oct_stats_strings[j]);
			data += ETH_GSTRING_LEN;
		}

		num_iq_stats = ARRAY_SIZE(oct_iq_stats_strings);
		for (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct_dev); i++) {
			if (!(oct_dev->io_qmask.iq & BIT_ULL(i)))
				continue;
			for (j = 0; j < num_iq_stats; j++) {
				sprintf(data, "tx-%d-%s", i,
					oct_iq_stats_strings[j]);
				data += ETH_GSTRING_LEN;
			}
		}

		num_oq_stats = ARRAY_SIZE(oct_droq_stats_strings);
		for (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct_dev); i++) {
			if (!(oct_dev->io_qmask.oq & BIT_ULL(i)))
				continue;
			for (j = 0; j < num_oq_stats; j++) {
				sprintf(data, "rx-%d-%s", i,
					oct_droq_stats_strings[j]);
				data += ETH_GSTRING_LEN;
			}
		}
		break;

	case ETH_SS_PRIV_FLAGS:
		lio_get_priv_flags_strings(lio, data);
		break;
	default:
		netif_info(lio, drv, lio->netdev, "Unknown Stringset !!\n");
		break;
	}
}