#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ptp_en; int /*<<< orphan*/  ext_clk_in; int /*<<< orphan*/  ext_clk_en; } ;
union cvmx_mio_ptp_clock_cfg {int u64; TYPE_1__ s; } ;
struct TYPE_4__ {int ptp_mode; } ;
union cvmx_agl_gmx_rxx_frm_ctl {int u64; TYPE_2__ s; } ;
typedef  int u64 ;
struct octeon_mgmt {int has_rx_tstamp; scalar_t__ agl; } ;
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 scalar_t__ AGL_GMX_RX_FRM_CTL ; 
 scalar_t__ CVMX_MIO_PTP_CLOCK_CFG ; 
 scalar_t__ CVMX_MIO_PTP_CLOCK_COMP ; 
 int EFAULT ; 
 int EINVAL ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 145 
#define  HWTSTAMP_FILTER_NONE 144 
#define  HWTSTAMP_FILTER_NTP_ALL 143 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 142 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 141 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 140 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 139 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 138 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 136 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 135 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 133 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 132 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 131 
#define  HWTSTAMP_FILTER_SOME 130 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 void* cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,...) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int octeon_get_io_clock_rate () ; 

__attribute__((used)) static int octeon_mgmt_ioctl_hwtstamp(struct net_device *netdev,
				      struct ifreq *rq, int cmd)
{
	struct octeon_mgmt *p = netdev_priv(netdev);
	struct hwtstamp_config config;
	union cvmx_mio_ptp_clock_cfg ptp;
	union cvmx_agl_gmx_rxx_frm_ctl rxx_frm_ctl;
	bool have_hw_timestamps = false;

	if (copy_from_user(&config, rq->ifr_data, sizeof(config)))
		return -EFAULT;

	if (config.flags) /* reserved for future extensions */
		return -EINVAL;

	/* Check the status of hardware for tiemstamps */
	if (OCTEON_IS_MODEL(OCTEON_CN6XXX)) {
		/* Get the current state of the PTP clock */
		ptp.u64 = cvmx_read_csr(CVMX_MIO_PTP_CLOCK_CFG);
		if (!ptp.s.ext_clk_en) {
			/* The clock has not been configured to use an
			 * external source.  Program it to use the main clock
			 * reference.
			 */
			u64 clock_comp = (NSEC_PER_SEC << 32) /	octeon_get_io_clock_rate();
			if (!ptp.s.ptp_en)
				cvmx_write_csr(CVMX_MIO_PTP_CLOCK_COMP, clock_comp);
			netdev_info(netdev,
				    "PTP Clock using sclk reference @ %lldHz\n",
				    (NSEC_PER_SEC << 32) / clock_comp);
		} else {
			/* The clock is already programmed to use a GPIO */
			u64 clock_comp = cvmx_read_csr(CVMX_MIO_PTP_CLOCK_COMP);
			netdev_info(netdev,
				    "PTP Clock using GPIO%d @ %lld Hz\n",
				    ptp.s.ext_clk_in, (NSEC_PER_SEC << 32) / clock_comp);
		}

		/* Enable the clock if it wasn't done already */
		if (!ptp.s.ptp_en) {
			ptp.s.ptp_en = 1;
			cvmx_write_csr(CVMX_MIO_PTP_CLOCK_CFG, ptp.u64);
		}
		have_hw_timestamps = true;
	}

	if (!have_hw_timestamps)
		return -EINVAL;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
	case HWTSTAMP_TX_ON:
		break;
	default:
		return -ERANGE;
	}

	switch (config.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		p->has_rx_tstamp = false;
		rxx_frm_ctl.u64 = cvmx_read_csr(p->agl + AGL_GMX_RX_FRM_CTL);
		rxx_frm_ctl.s.ptp_mode = 0;
		cvmx_write_csr(p->agl + AGL_GMX_RX_FRM_CTL, rxx_frm_ctl.u64);
		break;
	case HWTSTAMP_FILTER_ALL:
	case HWTSTAMP_FILTER_SOME:
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_NTP_ALL:
		p->has_rx_tstamp = have_hw_timestamps;
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		if (p->has_rx_tstamp) {
			rxx_frm_ctl.u64 = cvmx_read_csr(p->agl + AGL_GMX_RX_FRM_CTL);
			rxx_frm_ctl.s.ptp_mode = 1;
			cvmx_write_csr(p->agl + AGL_GMX_RX_FRM_CTL, rxx_frm_ctl.u64);
		}
		break;
	default:
		return -ERANGE;
	}

	if (copy_to_user(rq->ifr_data, &config, sizeof(config)))
		return -EFAULT;

	return 0;
}