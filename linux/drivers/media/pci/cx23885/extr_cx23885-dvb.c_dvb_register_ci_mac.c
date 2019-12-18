#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {int /*<<< orphan*/  demux; } ;
struct vb2_dvb_frontend {TYPE_2__ dvb; } ;
struct sp2_config {int addr; int /*<<< orphan*/  type; struct sp2_config* platform_data; int /*<<< orphan*/  ci_control; struct cx23885_tsport* priv; TYPE_5__* dvb_adap; } ;
struct netup_card_info {TYPE_1__* port; } ;
struct TYPE_12__ {TYPE_3__* driver; } ;
struct i2c_client {TYPE_4__ dev; } ;
struct i2c_board_info {int addr; int /*<<< orphan*/  type; struct i2c_board_info* platform_data; int /*<<< orphan*/  ci_control; struct cx23885_tsport* priv; TYPE_5__* dvb_adap; } ;
struct TYPE_13__ {int /*<<< orphan*/ * proposed_mac; } ;
struct TYPE_14__ {TYPE_5__ adapter; } ;
struct cx23885_tsport {int nr; TYPE_6__ frontends; struct i2c_client* i2c_client_ci; struct cx23885_dev* dev; } ;
struct TYPE_15__ {int addr; } ;
struct cx23885_i2c {TYPE_7__ i2c_client; int /*<<< orphan*/  i2c_adap; } ;
struct cx23885_dev {int board; struct cx23885_i2c* i2c_bus; } ;
struct altera_ci_config {int /*<<< orphan*/  fpga_rw; int /*<<< orphan*/ * demux; TYPE_5__* adapter; struct cx23885_dev* dev; } ;
typedef  int /*<<< orphan*/  sp2_config ;
typedef  int /*<<< orphan*/  eeprom ;
struct TYPE_16__ {int name; } ;
struct TYPE_11__ {int /*<<< orphan*/  owner; } ;
struct TYPE_9__ {int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
#define  CX23885_BOARD_DVBSKY_S950 137 
#define  CX23885_BOARD_DVBSKY_S950C 136 
#define  CX23885_BOARD_DVBSKY_S952 135 
#define  CX23885_BOARD_DVBSKY_T9580 134 
#define  CX23885_BOARD_DVBSKY_T980C 133 
#define  CX23885_BOARD_DVBSKY_T982 132 
#define  CX23885_BOARD_NETUP_DUAL_DVBS2_CI 131 
#define  CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF 130 
#define  CX23885_BOARD_TEVII_S470 129 
#define  CX23885_BOARD_TT_CT2_4500_CI 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  altera_ci_init (struct altera_ci_config*,int) ; 
 TYPE_8__* cx23885_boards ; 
 int /*<<< orphan*/  cx23885_sp2_ci_ctrl ; 
 struct i2c_client* i2c_new_device (int /*<<< orphan*/ *,struct sp2_config*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sp2_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netup_altera_fpga_rw ; 
 int /*<<< orphan*/  netup_ci_init (struct cx23885_tsport*) ; 
 int /*<<< orphan*/  netup_get_card_info (int /*<<< orphan*/ *,struct netup_card_info*) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 int /*<<< orphan*/  request_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tveeprom_read (TYPE_7__*,int /*<<< orphan*/ *,int) ; 
 struct vb2_dvb_frontend* vb2_dvb_get_frontend (TYPE_6__*,int) ; 

__attribute__((used)) static int dvb_register_ci_mac(struct cx23885_tsport *port)
{
	struct cx23885_dev *dev = port->dev;
	struct i2c_client *client_ci = NULL;
	struct vb2_dvb_frontend *fe0;

	fe0 = vb2_dvb_get_frontend(&port->frontends, 1);
	if (!fe0)
		return -EINVAL;

	switch (dev->board) {
	case CX23885_BOARD_NETUP_DUAL_DVBS2_CI: {
		static struct netup_card_info cinfo;

		netup_get_card_info(&dev->i2c_bus[0].i2c_adap, &cinfo);
		memcpy(port->frontends.adapter.proposed_mac,
				cinfo.port[port->nr - 1].mac, 6);
		pr_info("NetUP Dual DVB-S2 CI card port%d MAC=%pM\n",
			port->nr, port->frontends.adapter.proposed_mac);

		netup_ci_init(port);
		return 0;
		}
	case CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF: {
		struct altera_ci_config netup_ci_cfg = {
			.dev = dev,/* magic number to identify*/
			.adapter = &port->frontends.adapter,/* for CI */
			.demux = &fe0->dvb.demux,/* for hw pid filter */
			.fpga_rw = netup_altera_fpga_rw,
		};

		altera_ci_init(&netup_ci_cfg, port->nr);
		return 0;
		}
	case CX23885_BOARD_TEVII_S470: {
		u8 eeprom[256]; /* 24C02 i2c eeprom */

		if (port->nr != 1)
			return 0;

		/* Read entire EEPROM */
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_read(&dev->i2c_bus[0].i2c_client, eeprom, sizeof(eeprom));
		pr_info("TeVii S470 MAC= %pM\n", eeprom + 0xa0);
		memcpy(port->frontends.adapter.proposed_mac, eeprom + 0xa0, 6);
		return 0;
		}
	case CX23885_BOARD_DVBSKY_T9580:
	case CX23885_BOARD_DVBSKY_S950:
	case CX23885_BOARD_DVBSKY_S952:
	case CX23885_BOARD_DVBSKY_T982: {
		u8 eeprom[256]; /* 24C02 i2c eeprom */

		if (port->nr > 2)
			return 0;

		/* Read entire EEPROM */
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_read(&dev->i2c_bus[0].i2c_client, eeprom,
				sizeof(eeprom));
		pr_info("%s port %d MAC address: %pM\n",
			cx23885_boards[dev->board].name, port->nr,
			eeprom + 0xc0 + (port->nr-1) * 8);
		memcpy(port->frontends.adapter.proposed_mac, eeprom + 0xc0 +
			(port->nr-1) * 8, 6);
		return 0;
		}
	case CX23885_BOARD_DVBSKY_S950C:
	case CX23885_BOARD_DVBSKY_T980C:
	case CX23885_BOARD_TT_CT2_4500_CI: {
		u8 eeprom[256]; /* 24C02 i2c eeprom */
		struct sp2_config sp2_config;
		struct i2c_board_info info;
		struct cx23885_i2c *i2c_bus = &dev->i2c_bus[0];

		/* attach CI */
		memset(&sp2_config, 0, sizeof(sp2_config));
		sp2_config.dvb_adap = &port->frontends.adapter;
		sp2_config.priv = port;
		sp2_config.ci_control = cx23885_sp2_ci_ctrl;
		memset(&info, 0, sizeof(struct i2c_board_info));
		strscpy(info.type, "sp2", I2C_NAME_SIZE);
		info.addr = 0x40;
		info.platform_data = &sp2_config;
		request_module(info.type);
		client_ci = i2c_new_device(&i2c_bus->i2c_adap, &info);
		if (client_ci == NULL || client_ci->dev.driver == NULL)
			return -ENODEV;
		if (!try_module_get(client_ci->dev.driver->owner)) {
			i2c_unregister_device(client_ci);
			return -ENODEV;
		}
		port->i2c_client_ci = client_ci;

		if (port->nr != 1)
			return 0;

		/* Read entire EEPROM */
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_read(&dev->i2c_bus[0].i2c_client, eeprom,
				sizeof(eeprom));
		pr_info("%s MAC address: %pM\n",
			cx23885_boards[dev->board].name, eeprom + 0xc0);
		memcpy(port->frontends.adapter.proposed_mac, eeprom + 0xc0, 6);
		return 0;
		}
	}
	return 0;
}