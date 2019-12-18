#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int obase; void* osize; } ;
union cvmx_mixx_oring1 {int u64; TYPE_3__ s; } ;
struct TYPE_21__ {scalar_t__ orhwm; } ;
union cvmx_mixx_orhwm {int u64; TYPE_8__ s; } ;
struct TYPE_17__ {int ibase; void* isize; } ;
union cvmx_mixx_iring1 {int u64; TYPE_4__ s; } ;
struct TYPE_20__ {scalar_t__ irhwm; } ;
union cvmx_mixx_irhwm {int u64; TYPE_7__ s; } ;
struct TYPE_22__ {int ithena; int othena; } ;
union cvmx_mixx_intena {int u64; TYPE_9__ s; } ;
struct TYPE_18__ {int crc_strip; int en; int mrq_hwm; int lendian; scalar_t__ nbtarb; scalar_t__ reset; } ;
union cvmx_mixx_ctl {int u64; TYPE_5__ s; } ;
struct TYPE_19__ {int mode; int enable; int comp; scalar_t__ drv_byp; scalar_t__ clktx_byp; scalar_t__ dllrst; scalar_t__ clkrst; } ;
union cvmx_agl_prtx_ctl {int u64; TYPE_6__ s; } ;
struct TYPE_12__ {int ptp_mode; int pre_align; int pad_len; int vlan_len; int pre_free; int ctl_mcst; int ctl_bck; int ctl_drp; int pre_strp; int pre_chk; scalar_t__ ctl_smac; } ;
union cvmx_agl_gmx_rxx_frm_ctl {int u64; TYPE_10__ s; } ;
struct TYPE_14__ {int en; } ;
union cvmx_agl_gmx_inf_mode {int u64; TYPE_1__ s; } ;
struct TYPE_15__ {int byp_en1; int nctl1; int pctl1; int byp_en; int nctl; int pctl; } ;
union cvmx_agl_gmx_drv_ctl {int u64; TYPE_2__ s; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct octeon_mgmt {int tx_ring_handle; int rx_ring_handle; void* tx_ring; int /*<<< orphan*/  dev; void* rx_ring; int /*<<< orphan*/  napi; scalar_t__ last_speed; scalar_t__ last_link; scalar_t__ agl; scalar_t__ has_rx_tstamp; scalar_t__ mix; scalar_t__ irq; scalar_t__ agl_prt_ctl; scalar_t__ port; scalar_t__ rx_current_fill; scalar_t__ rx_next_fill; scalar_t__ rx_next; scalar_t__ tx_current_fill; scalar_t__ tx_next_clean; scalar_t__ tx_next; } ;
struct net_device {TYPE_11__* phydev; int /*<<< orphan*/  name; int /*<<< orphan*/  mtu; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 scalar_t__ AGL_GMX_RX_FRM_CTL ; 
 scalar_t__ AGL_GMX_RX_STATS_CTL ; 
 scalar_t__ AGL_GMX_RX_STATS_PKTS_BAD ; 
 scalar_t__ AGL_GMX_RX_STATS_PKTS_DRP ; 
 scalar_t__ AGL_GMX_TX_STAT0 ; 
 scalar_t__ AGL_GMX_TX_STAT1 ; 
 scalar_t__ AGL_GMX_TX_STATS_CTL ; 
 scalar_t__ CVMX_AGL_GMX_DRV_CTL ; 
 scalar_t__ CVMX_AGL_GMX_INF_MODE ; 
 scalar_t__ CVMX_AGL_GMX_TX_IFG ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MIX_CTL ; 
 scalar_t__ MIX_INTENA ; 
 scalar_t__ MIX_IRHWM ; 
 scalar_t__ MIX_IRING1 ; 
 scalar_t__ MIX_ISR ; 
 scalar_t__ MIX_ORHWM ; 
 scalar_t__ MIX_ORING1 ; 
 int NS_PER_PHY_CLK ; 
 int /*<<< orphan*/  OCTEON_CN52XX_PASS1_X ; 
 int /*<<< orphan*/  OCTEON_CN56XX_PASS1_X ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 void* OCTEON_MGMT_RX_RING_SIZE ; 
 void* OCTEON_MGMT_TX_RING_SIZE ; 
 int cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 void* dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int linkmode_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  octeon_mgmt_change_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_mgmt_disable_link (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  octeon_mgmt_enable_link (struct octeon_mgmt*) ; 
 scalar_t__ octeon_mgmt_init_phy (struct net_device*) ; 
 int /*<<< orphan*/  octeon_mgmt_interrupt ; 
 int /*<<< orphan*/  octeon_mgmt_reset_hw (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  octeon_mgmt_rx_fill_ring (struct net_device*) ; 
 int /*<<< orphan*/  octeon_mgmt_set_mac_address (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  octeon_mgmt_update_link (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  phy_start_aneg (TYPE_11__*) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ring_size_to_bytes (void*) ; 

__attribute__((used)) static int octeon_mgmt_open(struct net_device *netdev)
{
	struct octeon_mgmt *p = netdev_priv(netdev);
	union cvmx_mixx_ctl mix_ctl;
	union cvmx_agl_gmx_inf_mode agl_gmx_inf_mode;
	union cvmx_mixx_oring1 oring1;
	union cvmx_mixx_iring1 iring1;
	union cvmx_agl_gmx_rxx_frm_ctl rxx_frm_ctl;
	union cvmx_mixx_irhwm mix_irhwm;
	union cvmx_mixx_orhwm mix_orhwm;
	union cvmx_mixx_intena mix_intena;
	struct sockaddr sa;

	/* Allocate ring buffers.  */
	p->tx_ring = kzalloc(ring_size_to_bytes(OCTEON_MGMT_TX_RING_SIZE),
			     GFP_KERNEL);
	if (!p->tx_ring)
		return -ENOMEM;
	p->tx_ring_handle =
		dma_map_single(p->dev, p->tx_ring,
			       ring_size_to_bytes(OCTEON_MGMT_TX_RING_SIZE),
			       DMA_BIDIRECTIONAL);
	p->tx_next = 0;
	p->tx_next_clean = 0;
	p->tx_current_fill = 0;


	p->rx_ring = kzalloc(ring_size_to_bytes(OCTEON_MGMT_RX_RING_SIZE),
			     GFP_KERNEL);
	if (!p->rx_ring)
		goto err_nomem;
	p->rx_ring_handle =
		dma_map_single(p->dev, p->rx_ring,
			       ring_size_to_bytes(OCTEON_MGMT_RX_RING_SIZE),
			       DMA_BIDIRECTIONAL);

	p->rx_next = 0;
	p->rx_next_fill = 0;
	p->rx_current_fill = 0;

	octeon_mgmt_reset_hw(p);

	mix_ctl.u64 = cvmx_read_csr(p->mix + MIX_CTL);

	/* Bring it out of reset if needed. */
	if (mix_ctl.s.reset) {
		mix_ctl.s.reset = 0;
		cvmx_write_csr(p->mix + MIX_CTL, mix_ctl.u64);
		do {
			mix_ctl.u64 = cvmx_read_csr(p->mix + MIX_CTL);
		} while (mix_ctl.s.reset);
	}

	if (OCTEON_IS_MODEL(OCTEON_CN5XXX)) {
		agl_gmx_inf_mode.u64 = 0;
		agl_gmx_inf_mode.s.en = 1;
		cvmx_write_csr(CVMX_AGL_GMX_INF_MODE, agl_gmx_inf_mode.u64);
	}
	if (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X)
		|| OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X)) {
		/* Force compensation values, as they are not
		 * determined properly by HW
		 */
		union cvmx_agl_gmx_drv_ctl drv_ctl;

		drv_ctl.u64 = cvmx_read_csr(CVMX_AGL_GMX_DRV_CTL);
		if (p->port) {
			drv_ctl.s.byp_en1 = 1;
			drv_ctl.s.nctl1 = 6;
			drv_ctl.s.pctl1 = 6;
		} else {
			drv_ctl.s.byp_en = 1;
			drv_ctl.s.nctl = 6;
			drv_ctl.s.pctl = 6;
		}
		cvmx_write_csr(CVMX_AGL_GMX_DRV_CTL, drv_ctl.u64);
	}

	oring1.u64 = 0;
	oring1.s.obase = p->tx_ring_handle >> 3;
	oring1.s.osize = OCTEON_MGMT_TX_RING_SIZE;
	cvmx_write_csr(p->mix + MIX_ORING1, oring1.u64);

	iring1.u64 = 0;
	iring1.s.ibase = p->rx_ring_handle >> 3;
	iring1.s.isize = OCTEON_MGMT_RX_RING_SIZE;
	cvmx_write_csr(p->mix + MIX_IRING1, iring1.u64);

	memcpy(sa.sa_data, netdev->dev_addr, ETH_ALEN);
	octeon_mgmt_set_mac_address(netdev, &sa);

	octeon_mgmt_change_mtu(netdev, netdev->mtu);

	/* Enable the port HW. Packets are not allowed until
	 * cvmx_mgmt_port_enable() is called.
	 */
	mix_ctl.u64 = 0;
	mix_ctl.s.crc_strip = 1;    /* Strip the ending CRC */
	mix_ctl.s.en = 1;           /* Enable the port */
	mix_ctl.s.nbtarb = 0;       /* Arbitration mode */
	/* MII CB-request FIFO programmable high watermark */
	mix_ctl.s.mrq_hwm = 1;
#ifdef __LITTLE_ENDIAN
	mix_ctl.s.lendian = 1;
#endif
	cvmx_write_csr(p->mix + MIX_CTL, mix_ctl.u64);

	/* Read the PHY to find the mode of the interface. */
	if (octeon_mgmt_init_phy(netdev)) {
		dev_err(p->dev, "Cannot initialize PHY on MIX%d.\n", p->port);
		goto err_noirq;
	}

	/* Set the mode of the interface, RGMII/MII. */
	if (OCTEON_IS_MODEL(OCTEON_CN6XXX) && netdev->phydev) {
		union cvmx_agl_prtx_ctl agl_prtx_ctl;
		int rgmii_mode =
			(linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
					   netdev->phydev->supported) |
			 linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
					   netdev->phydev->supported)) != 0;

		agl_prtx_ctl.u64 = cvmx_read_csr(p->agl_prt_ctl);
		agl_prtx_ctl.s.mode = rgmii_mode ? 0 : 1;
		cvmx_write_csr(p->agl_prt_ctl,	agl_prtx_ctl.u64);

		/* MII clocks counts are based on the 125Mhz
		 * reference, which has an 8nS period. So our delays
		 * need to be multiplied by this factor.
		 */
#define NS_PER_PHY_CLK 8

		/* Take the DLL and clock tree out of reset */
		agl_prtx_ctl.u64 = cvmx_read_csr(p->agl_prt_ctl);
		agl_prtx_ctl.s.clkrst = 0;
		if (rgmii_mode) {
			agl_prtx_ctl.s.dllrst = 0;
			agl_prtx_ctl.s.clktx_byp = 0;
		}
		cvmx_write_csr(p->agl_prt_ctl,	agl_prtx_ctl.u64);
		cvmx_read_csr(p->agl_prt_ctl); /* Force write out before wait */

		/* Wait for the DLL to lock. External 125 MHz
		 * reference clock must be stable at this point.
		 */
		ndelay(256 * NS_PER_PHY_CLK);

		/* Enable the interface */
		agl_prtx_ctl.u64 = cvmx_read_csr(p->agl_prt_ctl);
		agl_prtx_ctl.s.enable = 1;
		cvmx_write_csr(p->agl_prt_ctl, agl_prtx_ctl.u64);

		/* Read the value back to force the previous write */
		agl_prtx_ctl.u64 = cvmx_read_csr(p->agl_prt_ctl);

		/* Enable the compensation controller */
		agl_prtx_ctl.s.comp = 1;
		agl_prtx_ctl.s.drv_byp = 0;
		cvmx_write_csr(p->agl_prt_ctl,	agl_prtx_ctl.u64);
		/* Force write out before wait. */
		cvmx_read_csr(p->agl_prt_ctl);

		/* For compensation state to lock. */
		ndelay(1040 * NS_PER_PHY_CLK);

		/* Default Interframe Gaps are too small.  Recommended
		 * workaround is.
		 *
		 * AGL_GMX_TX_IFG[IFG1]=14
		 * AGL_GMX_TX_IFG[IFG2]=10
		 */
		cvmx_write_csr(CVMX_AGL_GMX_TX_IFG, 0xae);
	}

	octeon_mgmt_rx_fill_ring(netdev);

	/* Clear statistics. */
	/* Clear on read. */
	cvmx_write_csr(p->agl + AGL_GMX_RX_STATS_CTL, 1);
	cvmx_write_csr(p->agl + AGL_GMX_RX_STATS_PKTS_DRP, 0);
	cvmx_write_csr(p->agl + AGL_GMX_RX_STATS_PKTS_BAD, 0);

	cvmx_write_csr(p->agl + AGL_GMX_TX_STATS_CTL, 1);
	cvmx_write_csr(p->agl + AGL_GMX_TX_STAT0, 0);
	cvmx_write_csr(p->agl + AGL_GMX_TX_STAT1, 0);

	/* Clear any pending interrupts */
	cvmx_write_csr(p->mix + MIX_ISR, cvmx_read_csr(p->mix + MIX_ISR));

	if (request_irq(p->irq, octeon_mgmt_interrupt, 0, netdev->name,
			netdev)) {
		dev_err(p->dev, "request_irq(%d) failed.\n", p->irq);
		goto err_noirq;
	}

	/* Interrupt every single RX packet */
	mix_irhwm.u64 = 0;
	mix_irhwm.s.irhwm = 0;
	cvmx_write_csr(p->mix + MIX_IRHWM, mix_irhwm.u64);

	/* Interrupt when we have 1 or more packets to clean.  */
	mix_orhwm.u64 = 0;
	mix_orhwm.s.orhwm = 0;
	cvmx_write_csr(p->mix + MIX_ORHWM, mix_orhwm.u64);

	/* Enable receive and transmit interrupts */
	mix_intena.u64 = 0;
	mix_intena.s.ithena = 1;
	mix_intena.s.othena = 1;
	cvmx_write_csr(p->mix + MIX_INTENA, mix_intena.u64);

	/* Enable packet I/O. */

	rxx_frm_ctl.u64 = 0;
	rxx_frm_ctl.s.ptp_mode = p->has_rx_tstamp ? 1 : 0;
	rxx_frm_ctl.s.pre_align = 1;
	/* When set, disables the length check for non-min sized pkts
	 * with padding in the client data.
	 */
	rxx_frm_ctl.s.pad_len = 1;
	/* When set, disables the length check for VLAN pkts */
	rxx_frm_ctl.s.vlan_len = 1;
	/* When set, PREAMBLE checking is  less strict */
	rxx_frm_ctl.s.pre_free = 1;
	/* Control Pause Frames can match station SMAC */
	rxx_frm_ctl.s.ctl_smac = 0;
	/* Control Pause Frames can match globally assign Multicast address */
	rxx_frm_ctl.s.ctl_mcst = 1;
	/* Forward pause information to TX block */
	rxx_frm_ctl.s.ctl_bck = 1;
	/* Drop Control Pause Frames */
	rxx_frm_ctl.s.ctl_drp = 1;
	/* Strip off the preamble */
	rxx_frm_ctl.s.pre_strp = 1;
	/* This port is configured to send PREAMBLE+SFD to begin every
	 * frame.  GMX checks that the PREAMBLE is sent correctly.
	 */
	rxx_frm_ctl.s.pre_chk = 1;
	cvmx_write_csr(p->agl + AGL_GMX_RX_FRM_CTL, rxx_frm_ctl.u64);

	/* Configure the port duplex, speed and enables */
	octeon_mgmt_disable_link(p);
	if (netdev->phydev)
		octeon_mgmt_update_link(p);
	octeon_mgmt_enable_link(p);

	p->last_link = 0;
	p->last_speed = 0;
	/* PHY is not present in simulator. The carrier is enabled
	 * while initializing the phy for simulator, leave it enabled.
	 */
	if (netdev->phydev) {
		netif_carrier_off(netdev);
		phy_start_aneg(netdev->phydev);
	}

	netif_wake_queue(netdev);
	napi_enable(&p->napi);

	return 0;
err_noirq:
	octeon_mgmt_reset_hw(p);
	dma_unmap_single(p->dev, p->rx_ring_handle,
			 ring_size_to_bytes(OCTEON_MGMT_RX_RING_SIZE),
			 DMA_BIDIRECTIONAL);
	kfree(p->rx_ring);
err_nomem:
	dma_unmap_single(p->dev, p->tx_ring_handle,
			 ring_size_to_bytes(OCTEON_MGMT_TX_RING_SIZE),
			 DMA_BIDIRECTIONAL);
	kfree(p->tx_ring);
	return -ENOMEM;
}