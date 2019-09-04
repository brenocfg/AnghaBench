#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mt7530_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  reset; int /*<<< orphan*/  rstc; scalar_t__ mcm; int /*<<< orphan*/  io_pwr; int /*<<< orphan*/  core_pwr; int /*<<< orphan*/  ethernet; } ;
struct mt7530_dummy_poll {int dummy; } ;
struct dsa_switch {TYPE_4__* ports; struct mt7530_priv* priv; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {TYPE_3__* master; } ;
struct TYPE_6__ {TYPE_1__* of_node; } ;
struct TYPE_7__ {TYPE_2__ dev; } ;
struct TYPE_5__ {struct device_node* parent; } ;

/* Variables and functions */
 int CHIP_NAME_SHIFT ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_MT7530_DUMMY_POLL (struct mt7530_dummy_poll*,struct mt7530_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MHWTRAP_MANUAL ; 
 int MHWTRAP_P6_DIS ; 
 int MHWTRAP_PHY_ACCESS ; 
 size_t MT7530_CPU_PORT ; 
 int /*<<< orphan*/  MT7530_CREV ; 
 int /*<<< orphan*/  MT7530_FDB_FLUSH ; 
 int /*<<< orphan*/  MT7530_HWTRAP ; 
 int MT7530_ID ; 
 int /*<<< orphan*/  MT7530_MFC ; 
 int /*<<< orphan*/  MT7530_MHWTRAP ; 
 int MT7530_NUM_PORTS ; 
 int /*<<< orphan*/  MT7530_PCR_P (int) ; 
 int /*<<< orphan*/  MT7530_SYS_CTRL ; 
 int /*<<< orphan*/  PCR_MATRIX_CLR ; 
 int /*<<< orphan*/  PCR_MATRIX_MASK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SYS_CTRL_PHY_RST ; 
 int SYS_CTRL_REG_RST ; 
 int SYS_CTRL_SW_RST ; 
 int /*<<< orphan*/  UNU_FFP_MASK ; 
 int /*<<< orphan*/  _mt7530_read ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt7530_clear (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_cpu_port_enable (struct mt7530_priv*,int) ; 
 int mt7530_fdb_cmd (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7530_mib_reset (struct dsa_switch*) ; 
 int /*<<< orphan*/  mt7530_port_disable (struct dsa_switch*,int,int /*<<< orphan*/ *) ; 
 int mt7530_read (struct mt7530_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_rmw (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_write (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct mt7530_dummy_poll*,int,int,int,int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_set_voltage (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
mt7530_setup(struct dsa_switch *ds)
{
	struct mt7530_priv *priv = ds->priv;
	int ret, i;
	u32 id, val;
	struct device_node *dn;
	struct mt7530_dummy_poll p;

	/* The parent node of master netdev which holds the common system
	 * controller also is the container for two GMACs nodes representing
	 * as two netdev instances.
	 */
	dn = ds->ports[MT7530_CPU_PORT].master->dev.of_node->parent;
	priv->ethernet = syscon_node_to_regmap(dn);
	if (IS_ERR(priv->ethernet))
		return PTR_ERR(priv->ethernet);

	regulator_set_voltage(priv->core_pwr, 1000000, 1000000);
	ret = regulator_enable(priv->core_pwr);
	if (ret < 0) {
		dev_err(priv->dev,
			"Failed to enable core power: %d\n", ret);
		return ret;
	}

	regulator_set_voltage(priv->io_pwr, 3300000, 3300000);
	ret = regulator_enable(priv->io_pwr);
	if (ret < 0) {
		dev_err(priv->dev, "Failed to enable io pwr: %d\n",
			ret);
		return ret;
	}

	/* Reset whole chip through gpio pin or memory-mapped registers for
	 * different type of hardware
	 */
	if (priv->mcm) {
		reset_control_assert(priv->rstc);
		usleep_range(1000, 1100);
		reset_control_deassert(priv->rstc);
	} else {
		gpiod_set_value_cansleep(priv->reset, 0);
		usleep_range(1000, 1100);
		gpiod_set_value_cansleep(priv->reset, 1);
	}

	/* Waiting for MT7530 got to stable */
	INIT_MT7530_DUMMY_POLL(&p, priv, MT7530_HWTRAP);
	ret = readx_poll_timeout(_mt7530_read, &p, val, val != 0,
				 20, 1000000);
	if (ret < 0) {
		dev_err(priv->dev, "reset timeout\n");
		return ret;
	}

	id = mt7530_read(priv, MT7530_CREV);
	id >>= CHIP_NAME_SHIFT;
	if (id != MT7530_ID) {
		dev_err(priv->dev, "chip %x can't be supported\n", id);
		return -ENODEV;
	}

	/* Reset the switch through internal reset */
	mt7530_write(priv, MT7530_SYS_CTRL,
		     SYS_CTRL_PHY_RST | SYS_CTRL_SW_RST |
		     SYS_CTRL_REG_RST);

	/* Enable Port 6 only; P5 as GMAC5 which currently is not supported */
	val = mt7530_read(priv, MT7530_MHWTRAP);
	val &= ~MHWTRAP_P6_DIS & ~MHWTRAP_PHY_ACCESS;
	val |= MHWTRAP_MANUAL;
	mt7530_write(priv, MT7530_MHWTRAP, val);

	/* Enable and reset MIB counters */
	mt7530_mib_reset(ds);

	mt7530_clear(priv, MT7530_MFC, UNU_FFP_MASK);

	for (i = 0; i < MT7530_NUM_PORTS; i++) {
		/* Disable forwarding by default on all ports */
		mt7530_rmw(priv, MT7530_PCR_P(i), PCR_MATRIX_MASK,
			   PCR_MATRIX_CLR);

		if (dsa_is_cpu_port(ds, i))
			mt7530_cpu_port_enable(priv, i);
		else
			mt7530_port_disable(ds, i, NULL);
	}

	/* Flush the FDB table */
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_FLUSH, NULL);
	if (ret < 0)
		return ret;

	return 0;
}