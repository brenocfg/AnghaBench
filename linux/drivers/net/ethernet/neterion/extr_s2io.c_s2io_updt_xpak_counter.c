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
typedef  int u64 ;
typedef  int u16 ;
struct xpakStat {int /*<<< orphan*/  warn_laser_output_power_low; int /*<<< orphan*/  warn_laser_output_power_high; int /*<<< orphan*/  warn_laser_bias_current_low; int /*<<< orphan*/  warn_laser_bias_current_high; int /*<<< orphan*/  warn_transceiver_temp_low; int /*<<< orphan*/  warn_transceiver_temp_high; int /*<<< orphan*/  alarm_laser_output_power_low; int /*<<< orphan*/  xpak_regs_stat; int /*<<< orphan*/  alarm_laser_output_power_high; int /*<<< orphan*/  alarm_laser_bias_current_low; int /*<<< orphan*/  alarm_laser_bias_current_high; int /*<<< orphan*/  alarm_transceiver_temp_low; int /*<<< orphan*/  alarm_transceiver_temp_high; } ;
struct stat_block {struct xpakStat xpak_stat; } ;
struct TYPE_2__ {struct stat_block* stats_info; } ;
struct s2io_nic {TYPE_1__ mac_control; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CHECKBIT (int,int) ; 
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 int MDIO_CTRL1 ; 
 int MDIO_CTRL1_SPEED10G ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  s2io_chk_xpak_counter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int s2io_mdio_read (int /*<<< orphan*/ ,int,struct net_device*) ; 
 int /*<<< orphan*/  s2io_mdio_write (int /*<<< orphan*/ ,int,int,struct net_device*) ; 

__attribute__((used)) static void s2io_updt_xpak_counter(struct net_device *dev)
{
	u16 flag  = 0x0;
	u16 type  = 0x0;
	u16 val16 = 0x0;
	u64 val64 = 0x0;
	u64 addr  = 0x0;

	struct s2io_nic *sp = netdev_priv(dev);
	struct stat_block *stats = sp->mac_control.stats_info;
	struct xpakStat *xstats = &stats->xpak_stat;

	/* Check the communication with the MDIO slave */
	addr = MDIO_CTRL1;
	val64 = 0x0;
	val64 = s2io_mdio_read(MDIO_MMD_PMAPMD, addr, dev);
	if ((val64 == 0xFFFF) || (val64 == 0x0000)) {
		DBG_PRINT(ERR_DBG,
			  "ERR: MDIO slave access failed - Returned %llx\n",
			  (unsigned long long)val64);
		return;
	}

	/* Check for the expected value of control reg 1 */
	if (val64 != MDIO_CTRL1_SPEED10G) {
		DBG_PRINT(ERR_DBG, "Incorrect value at PMA address 0x0000 - "
			  "Returned: %llx- Expected: 0x%x\n",
			  (unsigned long long)val64, MDIO_CTRL1_SPEED10G);
		return;
	}

	/* Loading the DOM register to MDIO register */
	addr = 0xA100;
	s2io_mdio_write(MDIO_MMD_PMAPMD, addr, val16, dev);
	val64 = s2io_mdio_read(MDIO_MMD_PMAPMD, addr, dev);

	/* Reading the Alarm flags */
	addr = 0xA070;
	val64 = 0x0;
	val64 = s2io_mdio_read(MDIO_MMD_PMAPMD, addr, dev);

	flag = CHECKBIT(val64, 0x7);
	type = 1;
	s2io_chk_xpak_counter(&xstats->alarm_transceiver_temp_high,
			      &xstats->xpak_regs_stat,
			      0x0, flag, type);

	if (CHECKBIT(val64, 0x6))
		xstats->alarm_transceiver_temp_low++;

	flag = CHECKBIT(val64, 0x3);
	type = 2;
	s2io_chk_xpak_counter(&xstats->alarm_laser_bias_current_high,
			      &xstats->xpak_regs_stat,
			      0x2, flag, type);

	if (CHECKBIT(val64, 0x2))
		xstats->alarm_laser_bias_current_low++;

	flag = CHECKBIT(val64, 0x1);
	type = 3;
	s2io_chk_xpak_counter(&xstats->alarm_laser_output_power_high,
			      &xstats->xpak_regs_stat,
			      0x4, flag, type);

	if (CHECKBIT(val64, 0x0))
		xstats->alarm_laser_output_power_low++;

	/* Reading the Warning flags */
	addr = 0xA074;
	val64 = 0x0;
	val64 = s2io_mdio_read(MDIO_MMD_PMAPMD, addr, dev);

	if (CHECKBIT(val64, 0x7))
		xstats->warn_transceiver_temp_high++;

	if (CHECKBIT(val64, 0x6))
		xstats->warn_transceiver_temp_low++;

	if (CHECKBIT(val64, 0x3))
		xstats->warn_laser_bias_current_high++;

	if (CHECKBIT(val64, 0x2))
		xstats->warn_laser_bias_current_low++;

	if (CHECKBIT(val64, 0x1))
		xstats->warn_laser_output_power_high++;

	if (CHECKBIT(val64, 0x0))
		xstats->warn_laser_output_power_low++;
}