#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {scalar_t__ max_speed_hz; TYPE_1__ dev; int /*<<< orphan*/  mode; } ;
struct qcaspi {struct net_device* net_dev; int /*<<< orphan*/  legacy_mode; struct spi_device* spi_dev; } ;
struct net_device {scalar_t__ name; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (char const*) ; 
 scalar_t__ QCASPI_BURST_LEN_MAX ; 
 scalar_t__ QCASPI_BURST_LEN_MIN ; 
 scalar_t__ QCASPI_CLK_SPEED ; 
 scalar_t__ QCASPI_CLK_SPEED_MAX ; 
 scalar_t__ QCASPI_CLK_SPEED_MIN ; 
 int /*<<< orphan*/  QCASPI_DRV_VERSION ; 
 scalar_t__ QCASPI_GOOD_SIGNATURE ; 
 scalar_t__ QCASPI_PLUGGABLE_MAX ; 
 scalar_t__ QCASPI_PLUGGABLE_MIN ; 
 scalar_t__ QCASPI_WRITE_VERIFY_MAX ; 
 scalar_t__ QCASPI_WRITE_VERIFY_MIN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  SPI_REG_SIGNATURE ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 char* of_get_mac_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ qcaspi_burst_len ; 
 scalar_t__ qcaspi_clkspeed ; 
 int /*<<< orphan*/  qcaspi_init_device_debugfs (struct qcaspi*) ; 
 int /*<<< orphan*/  qcaspi_netdev_setup (struct net_device*) ; 
 scalar_t__ qcaspi_pluggable ; 
 int /*<<< orphan*/  qcaspi_read_register (struct qcaspi*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct net_device*) ; 
 scalar_t__ spi_setup (struct spi_device*) ; 
 scalar_t__ wr_verify ; 

__attribute__((used)) static int
qca_spi_probe(struct spi_device *spi)
{
	struct qcaspi *qca = NULL;
	struct net_device *qcaspi_devs = NULL;
	u8 legacy_mode = 0;
	u16 signature;
	const char *mac;

	if (!spi->dev.of_node) {
		dev_err(&spi->dev, "Missing device tree\n");
		return -EINVAL;
	}

	legacy_mode = of_property_read_bool(spi->dev.of_node,
					    "qca,legacy-mode");

	if (qcaspi_clkspeed == 0) {
		if (spi->max_speed_hz)
			qcaspi_clkspeed = spi->max_speed_hz;
		else
			qcaspi_clkspeed = QCASPI_CLK_SPEED;
	}

	if ((qcaspi_clkspeed < QCASPI_CLK_SPEED_MIN) ||
	    (qcaspi_clkspeed > QCASPI_CLK_SPEED_MAX)) {
		dev_err(&spi->dev, "Invalid clkspeed: %d\n",
			qcaspi_clkspeed);
		return -EINVAL;
	}

	if ((qcaspi_burst_len < QCASPI_BURST_LEN_MIN) ||
	    (qcaspi_burst_len > QCASPI_BURST_LEN_MAX)) {
		dev_err(&spi->dev, "Invalid burst len: %d\n",
			qcaspi_burst_len);
		return -EINVAL;
	}

	if ((qcaspi_pluggable < QCASPI_PLUGGABLE_MIN) ||
	    (qcaspi_pluggable > QCASPI_PLUGGABLE_MAX)) {
		dev_err(&spi->dev, "Invalid pluggable: %d\n",
			qcaspi_pluggable);
		return -EINVAL;
	}

	if (wr_verify < QCASPI_WRITE_VERIFY_MIN ||
	    wr_verify > QCASPI_WRITE_VERIFY_MAX) {
		dev_err(&spi->dev, "Invalid write verify: %d\n",
			wr_verify);
		return -EINVAL;
	}

	dev_info(&spi->dev, "ver=%s, clkspeed=%d, burst_len=%d, pluggable=%d\n",
		 QCASPI_DRV_VERSION,
		 qcaspi_clkspeed,
		 qcaspi_burst_len,
		 qcaspi_pluggable);

	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = qcaspi_clkspeed;
	if (spi_setup(spi) < 0) {
		dev_err(&spi->dev, "Unable to setup SPI device\n");
		return -EFAULT;
	}

	qcaspi_devs = alloc_etherdev(sizeof(struct qcaspi));
	if (!qcaspi_devs)
		return -ENOMEM;

	qcaspi_netdev_setup(qcaspi_devs);
	SET_NETDEV_DEV(qcaspi_devs, &spi->dev);

	qca = netdev_priv(qcaspi_devs);
	if (!qca) {
		free_netdev(qcaspi_devs);
		dev_err(&spi->dev, "Fail to retrieve private structure\n");
		return -ENOMEM;
	}
	qca->net_dev = qcaspi_devs;
	qca->spi_dev = spi;
	qca->legacy_mode = legacy_mode;

	spi_set_drvdata(spi, qcaspi_devs);

	mac = of_get_mac_address(spi->dev.of_node);

	if (!IS_ERR(mac))
		ether_addr_copy(qca->net_dev->dev_addr, mac);

	if (!is_valid_ether_addr(qca->net_dev->dev_addr)) {
		eth_hw_addr_random(qca->net_dev);
		dev_info(&spi->dev, "Using random MAC address: %pM\n",
			 qca->net_dev->dev_addr);
	}

	netif_carrier_off(qca->net_dev);

	if (!qcaspi_pluggable) {
		qcaspi_read_register(qca, SPI_REG_SIGNATURE, &signature);
		qcaspi_read_register(qca, SPI_REG_SIGNATURE, &signature);

		if (signature != QCASPI_GOOD_SIGNATURE) {
			dev_err(&spi->dev, "Invalid signature (0x%04X)\n",
				signature);
			free_netdev(qcaspi_devs);
			return -EFAULT;
		}
	}

	if (register_netdev(qcaspi_devs)) {
		dev_err(&spi->dev, "Unable to register net device %s\n",
			qcaspi_devs->name);
		free_netdev(qcaspi_devs);
		return -EFAULT;
	}

	qcaspi_init_device_debugfs(qca);

	return 0;
}