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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ocelot {int num_phys_ports; int num_stats; int /*<<< orphan*/  dev; scalar_t__ ptp; int /*<<< orphan*/  stats_work; int /*<<< orphan*/  stats_queue; int /*<<< orphan*/ * regfields; int /*<<< orphan*/  ptp_clock_lock; int /*<<< orphan*/  ptp_lock; int /*<<< orphan*/  stats_lock; void* stats; void* lags; } ;
typedef  int /*<<< orphan*/  queue_name ;

/* Variables and functions */
 size_t ANA_ADVLEARN_VLAN_CHK ; 
 int /*<<< orphan*/  ANA_AGGR_CFG ; 
 int ANA_AGGR_CFG_AC_DMAC_ENA ; 
 int ANA_AGGR_CFG_AC_IP4_SIPDIP_ENA ; 
 int ANA_AGGR_CFG_AC_IP4_TCPUDP_ENA ; 
 int ANA_AGGR_CFG_AC_SMAC_ENA ; 
 int /*<<< orphan*/  ANA_AUTOAGE ; 
 int ANA_AUTOAGE_AGE_PERIOD (int) ; 
 int /*<<< orphan*/  ANA_CPUQ_8021_CFG ; 
 int ANA_CPUQ_8021_CFG_CPUQ_BPDU_VAL (int) ; 
 int ANA_CPUQ_8021_CFG_CPUQ_GARP_VAL (int) ; 
 int /*<<< orphan*/  ANA_CPUQ_CFG ; 
 int ANA_CPUQ_CFG_CPUQ_ALLBRIDGE (int) ; 
 int ANA_CPUQ_CFG_CPUQ_IGMP (int) ; 
 int ANA_CPUQ_CFG_CPUQ_IPMC_CTRL (int) ; 
 int ANA_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE (int) ; 
 int ANA_CPUQ_CFG_CPUQ_LRN (int) ; 
 int ANA_CPUQ_CFG_CPUQ_MAC_COPY (int) ; 
 int ANA_CPUQ_CFG_CPUQ_MIRROR (int) ; 
 int ANA_CPUQ_CFG_CPUQ_MLD (int) ; 
 int ANA_CPUQ_CFG_CPUQ_SRC_COPY (int) ; 
 int /*<<< orphan*/  ANA_FLOODING ; 
 int ANA_FLOODING_FLD_BROADCAST (int) ; 
 int ANA_FLOODING_FLD_MULTICAST (int) ; 
 int ANA_FLOODING_FLD_UNICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ANA_FLOODING_IPMC ; 
 int ANA_FLOODING_IPMC_FLD_MC4_CTRL (int) ; 
 int ANA_FLOODING_IPMC_FLD_MC4_DATA (int) ; 
 int ANA_FLOODING_IPMC_FLD_MC6_CTRL (int) ; 
 int ANA_FLOODING_IPMC_FLD_MC6_DATA (int) ; 
 int /*<<< orphan*/  ANA_PGID_PGID ; 
 int ANA_PGID_PGID_PGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ANA_PORT_CPU_FWD_BPDU_CFG ; 
 int ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REDIR_ENA (int) ; 
 int /*<<< orphan*/  ANA_PORT_PORT_CFG ; 
 int ANA_PORT_PORT_CFG_PORTID_VAL (int) ; 
 int ANA_PORT_PORT_CFG_RECV_ENA ; 
 int BIT (int) ; 
 int BR_DEFAULT_AGEING_TIME ; 
 int ENOMEM ; 
 int ETH_P_8021AD ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCELOT_STATS_CHECK_DELAY ; 
 int PGID_CPU ; 
 int PGID_MC ; 
 int PGID_MCIPV4 ; 
 int PGID_MCIPV6 ; 
 int PGID_SRC ; 
 int /*<<< orphan*/  PGID_UC ; 
 int /*<<< orphan*/  QSYS_SWITCH_PORT_MODE ; 
 int QSYS_SWITCH_PORT_MODE_INGRESS_DROP_MODE ; 
 int QSYS_SWITCH_PORT_MODE_PORT_ENA ; 
 int QSYS_SWITCH_PORT_MODE_SCH_NEXT_CFG (int) ; 
 int /*<<< orphan*/  QS_INJ_GRP_CFG ; 
 int QS_INJ_GRP_CFG_BYTE_SWAP ; 
 int QS_INJ_GRP_CFG_MODE (int) ; 
 int /*<<< orphan*/  QS_XTR_GRP_CFG ; 
 int QS_XTR_GRP_CFG_BYTE_SWAP ; 
 int QS_XTR_GRP_CFG_MODE (int) ; 
 int /*<<< orphan*/  SYS_FRM_AGING ; 
 int SYS_FRM_AGING_AGE_TX_ENA ; 
 int SYS_FRM_AGING_MAX_AGE (int) ; 
 int /*<<< orphan*/  SYS_PORT_MODE ; 
 int SYS_PORT_MODE_INCL_INJ_HDR (int) ; 
 int SYS_PORT_MODE_INCL_XTR_HDR (int) ; 
 int /*<<< orphan*/  SYS_STAT_CFG ; 
 int SYS_STAT_CFG_STAT_CLEAR_SHOT (int) ; 
 int SYS_STAT_CFG_STAT_VIEW (int) ; 
 int /*<<< orphan*/  SYS_VLAN_ETYPE_CFG ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocelot_ace_init (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_check_stats_work ; 
 int ocelot_init_timestamp (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_mact_init (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_vlan_init (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocelot_write_rix (struct ocelot*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ocelot_init(struct ocelot *ocelot)
{
	u32 port;
	int i, ret, cpu = ocelot->num_phys_ports;
	char queue_name[32];

	ocelot->lags = devm_kcalloc(ocelot->dev, ocelot->num_phys_ports,
				    sizeof(u32), GFP_KERNEL);
	if (!ocelot->lags)
		return -ENOMEM;

	ocelot->stats = devm_kcalloc(ocelot->dev,
				     ocelot->num_phys_ports * ocelot->num_stats,
				     sizeof(u64), GFP_KERNEL);
	if (!ocelot->stats)
		return -ENOMEM;

	mutex_init(&ocelot->stats_lock);
	mutex_init(&ocelot->ptp_lock);
	spin_lock_init(&ocelot->ptp_clock_lock);
	snprintf(queue_name, sizeof(queue_name), "%s-stats",
		 dev_name(ocelot->dev));
	ocelot->stats_queue = create_singlethread_workqueue(queue_name);
	if (!ocelot->stats_queue)
		return -ENOMEM;

	ocelot_mact_init(ocelot);
	ocelot_vlan_init(ocelot);
	ocelot_ace_init(ocelot);

	for (port = 0; port < ocelot->num_phys_ports; port++) {
		/* Clear all counters (5 groups) */
		ocelot_write(ocelot, SYS_STAT_CFG_STAT_VIEW(port) |
				     SYS_STAT_CFG_STAT_CLEAR_SHOT(0x7f),
			     SYS_STAT_CFG);
	}

	/* Only use S-Tag */
	ocelot_write(ocelot, ETH_P_8021AD, SYS_VLAN_ETYPE_CFG);

	/* Aggregation mode */
	ocelot_write(ocelot, ANA_AGGR_CFG_AC_SMAC_ENA |
			     ANA_AGGR_CFG_AC_DMAC_ENA |
			     ANA_AGGR_CFG_AC_IP4_SIPDIP_ENA |
			     ANA_AGGR_CFG_AC_IP4_TCPUDP_ENA, ANA_AGGR_CFG);

	/* Set MAC age time to default value. The entry is aged after
	 * 2*AGE_PERIOD
	 */
	ocelot_write(ocelot,
		     ANA_AUTOAGE_AGE_PERIOD(BR_DEFAULT_AGEING_TIME / 2 / HZ),
		     ANA_AUTOAGE);

	/* Disable learning for frames discarded by VLAN ingress filtering */
	regmap_field_write(ocelot->regfields[ANA_ADVLEARN_VLAN_CHK], 1);

	/* Setup frame ageing - fixed value "2 sec" - in 6.5 us units */
	ocelot_write(ocelot, SYS_FRM_AGING_AGE_TX_ENA |
		     SYS_FRM_AGING_MAX_AGE(307692), SYS_FRM_AGING);

	/* Setup flooding PGIDs */
	ocelot_write_rix(ocelot, ANA_FLOODING_FLD_MULTICAST(PGID_MC) |
			 ANA_FLOODING_FLD_BROADCAST(PGID_MC) |
			 ANA_FLOODING_FLD_UNICAST(PGID_UC),
			 ANA_FLOODING, 0);
	ocelot_write(ocelot, ANA_FLOODING_IPMC_FLD_MC6_DATA(PGID_MCIPV6) |
		     ANA_FLOODING_IPMC_FLD_MC6_CTRL(PGID_MC) |
		     ANA_FLOODING_IPMC_FLD_MC4_DATA(PGID_MCIPV4) |
		     ANA_FLOODING_IPMC_FLD_MC4_CTRL(PGID_MC),
		     ANA_FLOODING_IPMC);

	for (port = 0; port < ocelot->num_phys_ports; port++) {
		/* Transmit the frame to the local port. */
		ocelot_write_rix(ocelot, BIT(port), ANA_PGID_PGID, port);
		/* Do not forward BPDU frames to the front ports. */
		ocelot_write_gix(ocelot,
				 ANA_PORT_CPU_FWD_BPDU_CFG_BPDU_REDIR_ENA(0xffff),
				 ANA_PORT_CPU_FWD_BPDU_CFG,
				 port);
		/* Ensure bridging is disabled */
		ocelot_write_rix(ocelot, 0, ANA_PGID_PGID, PGID_SRC + port);
	}

	/* Configure and enable the CPU port. */
	ocelot_write_rix(ocelot, 0, ANA_PGID_PGID, cpu);
	ocelot_write_rix(ocelot, BIT(cpu), ANA_PGID_PGID, PGID_CPU);
	ocelot_write_gix(ocelot, ANA_PORT_PORT_CFG_RECV_ENA |
			 ANA_PORT_PORT_CFG_PORTID_VAL(cpu),
			 ANA_PORT_PORT_CFG, cpu);

	/* Allow broadcast MAC frames. */
	for (i = ocelot->num_phys_ports + 1; i < PGID_CPU; i++) {
		u32 val = ANA_PGID_PGID_PGID(GENMASK(ocelot->num_phys_ports - 1, 0));

		ocelot_write_rix(ocelot, val, ANA_PGID_PGID, i);
	}
	ocelot_write_rix(ocelot,
			 ANA_PGID_PGID_PGID(GENMASK(ocelot->num_phys_ports, 0)),
			 ANA_PGID_PGID, PGID_MC);
	ocelot_write_rix(ocelot, 0, ANA_PGID_PGID, PGID_MCIPV4);
	ocelot_write_rix(ocelot, 0, ANA_PGID_PGID, PGID_MCIPV6);

	/* CPU port Injection/Extraction configuration */
	ocelot_write_rix(ocelot, QSYS_SWITCH_PORT_MODE_INGRESS_DROP_MODE |
			 QSYS_SWITCH_PORT_MODE_SCH_NEXT_CFG(1) |
			 QSYS_SWITCH_PORT_MODE_PORT_ENA,
			 QSYS_SWITCH_PORT_MODE, cpu);
	ocelot_write_rix(ocelot, SYS_PORT_MODE_INCL_XTR_HDR(1) |
			 SYS_PORT_MODE_INCL_INJ_HDR(1), SYS_PORT_MODE, cpu);
	/* Allow manual injection via DEVCPU_QS registers, and byte swap these
	 * registers endianness.
	 */
	ocelot_write_rix(ocelot, QS_INJ_GRP_CFG_BYTE_SWAP |
			 QS_INJ_GRP_CFG_MODE(1), QS_INJ_GRP_CFG, 0);
	ocelot_write_rix(ocelot, QS_XTR_GRP_CFG_BYTE_SWAP |
			 QS_XTR_GRP_CFG_MODE(1), QS_XTR_GRP_CFG, 0);
	ocelot_write(ocelot, ANA_CPUQ_CFG_CPUQ_MIRROR(2) |
		     ANA_CPUQ_CFG_CPUQ_LRN(2) |
		     ANA_CPUQ_CFG_CPUQ_MAC_COPY(2) |
		     ANA_CPUQ_CFG_CPUQ_SRC_COPY(2) |
		     ANA_CPUQ_CFG_CPUQ_LOCKED_PORTMOVE(2) |
		     ANA_CPUQ_CFG_CPUQ_ALLBRIDGE(6) |
		     ANA_CPUQ_CFG_CPUQ_IPMC_CTRL(6) |
		     ANA_CPUQ_CFG_CPUQ_IGMP(6) |
		     ANA_CPUQ_CFG_CPUQ_MLD(6), ANA_CPUQ_CFG);
	for (i = 0; i < 16; i++)
		ocelot_write_rix(ocelot, ANA_CPUQ_8021_CFG_CPUQ_GARP_VAL(6) |
				 ANA_CPUQ_8021_CFG_CPUQ_BPDU_VAL(6),
				 ANA_CPUQ_8021_CFG, i);

	INIT_DELAYED_WORK(&ocelot->stats_work, ocelot_check_stats_work);
	queue_delayed_work(ocelot->stats_queue, &ocelot->stats_work,
			   OCELOT_STATS_CHECK_DELAY);

	if (ocelot->ptp) {
		ret = ocelot_init_timestamp(ocelot);
		if (ret) {
			dev_err(ocelot->dev,
				"Timestamp initialization failed\n");
			return ret;
		}
	}

	return 0;
}