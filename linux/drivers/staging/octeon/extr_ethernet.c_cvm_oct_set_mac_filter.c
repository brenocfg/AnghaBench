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
union cvmx_gmxx_prtx_cfg {unsigned long long u64; } ;
typedef  int u8 ;
typedef  int u64 ;
struct octeon_ethernet {int /*<<< orphan*/  port; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM0 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM1 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM2 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM3 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM4 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM5 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_SMACX (int,int) ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_SPI ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_common_set_multicast_list (struct net_device*) ; 
 scalar_t__ cvmx_helper_interface_get_mode (int) ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cvm_oct_set_mac_filter(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	int interface = INTERFACE(priv->port);

	if ((interface < 2) &&
	    (cvmx_helper_interface_get_mode(interface) !=
		CVMX_HELPER_INTERFACE_MODE_SPI)) {
		int i;
		u8 *ptr = dev->dev_addr;
		u64 mac = 0;
		int index = INDEX(priv->port);

		for (i = 0; i < 6; i++)
			mac = (mac << 8) | (u64)ptr[i];

		gmx_cfg.u64 =
		    cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface),
			       gmx_cfg.u64 & ~1ull);

		cvmx_write_csr(CVMX_GMXX_SMACX(index, interface), mac);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM0(index, interface),
			       ptr[0]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM1(index, interface),
			       ptr[1]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM2(index, interface),
			       ptr[2]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM3(index, interface),
			       ptr[3]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM4(index, interface),
			       ptr[4]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM5(index, interface),
			       ptr[5]);
		cvm_oct_common_set_multicast_list(dev);
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface),
			       gmx_cfg.u64);
	}
	return 0;
}