#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pcterr; } ;
union cvmx_gmxx_rxx_int_reg {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
struct octeon_ethernet {int last_speed; int /*<<< orphan*/  port; int /*<<< orphan*/  link_info; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int speed; } ;
struct TYPE_6__ {TYPE_2__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_3__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_INT_REG (int,int) ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_set_hw_preamble (struct octeon_ethernet*,int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_register_lock ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cvm_oct_check_preamble_errors(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_helper_link_info_t link_info;
	unsigned long flags;

	link_info.u64 = priv->link_info;

	/*
	 * Take the global register lock since we are going to
	 * touch registers that affect more than one port.
	 */
	spin_lock_irqsave(&global_register_lock, flags);

	if (link_info.s.speed == 10 && priv->last_speed == 10) {
		/*
		 * Read the GMXX_RXX_INT_REG[PCTERR] bit and see if we are
		 * getting preamble errors.
		 */
		int interface = INTERFACE(priv->port);
		int index = INDEX(priv->port);
		union cvmx_gmxx_rxx_int_reg gmxx_rxx_int_reg;

		gmxx_rxx_int_reg.u64 = cvmx_read_csr(CVMX_GMXX_RXX_INT_REG
							(index, interface));
		if (gmxx_rxx_int_reg.s.pcterr) {
			/*
			 * We are getting preamble errors at 10Mbps. Most
			 * likely the PHY is giving us packets with misaligned
			 * preambles. In order to get these packets we need to
			 * disable preamble checking and do it in software.
			 */
			cvm_oct_set_hw_preamble(priv, false);
			printk_ratelimited("%s: Using 10Mbps with software preamble removal\n",
					   dev->name);
		}
	} else {
		/*
		 * Since the 10Mbps preamble workaround is allowed we need to
		 * enable preamble checking, FCS stripping, and clear error
		 * bits on every speed change. If errors occur during 10Mbps
		 * operation the above code will change this stuff
		 */
		if (priv->last_speed != link_info.s.speed)
			cvm_oct_set_hw_preamble(priv, true);
		priv->last_speed = link_info.s.speed;
	}
	spin_unlock_irqrestore(&global_register_lock, flags);
}