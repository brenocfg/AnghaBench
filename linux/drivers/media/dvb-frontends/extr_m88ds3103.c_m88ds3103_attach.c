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
struct m88ds3103_platform_data {int attach_in_use; struct dvb_frontend* (* get_dvb_frontend ) (struct i2c_client*) ;struct i2c_adapter* (* get_i2c_adapter ) (struct i2c_client*) ;int /*<<< orphan*/  lnb_en_pol; int /*<<< orphan*/  lnb_hv_pol; int /*<<< orphan*/  envelope_mode; int /*<<< orphan*/  clk_out; int /*<<< orphan*/  agc_inv; int /*<<< orphan*/  agc; int /*<<< orphan*/  spec_inv; int /*<<< orphan*/  ts_clk_pol; int /*<<< orphan*/  ts_clk; int /*<<< orphan*/  ts_mode; int /*<<< orphan*/  i2c_wr_max; int /*<<< orphan*/  clk; } ;
struct m88ds3103_config {int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/  lnb_en_pol; int /*<<< orphan*/  lnb_hv_pol; int /*<<< orphan*/  envelope_mode; int /*<<< orphan*/  clock_out; int /*<<< orphan*/  agc_inv; int /*<<< orphan*/  agc; int /*<<< orphan*/  spec_inv; int /*<<< orphan*/  ts_clk_pol; int /*<<< orphan*/  ts_clk; int /*<<< orphan*/  ts_mode; int /*<<< orphan*/  i2c_wr_max; int /*<<< orphan*/  clock; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct i2c_board_info {struct m88ds3103_platform_data* platform_data; int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  board_info ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct i2c_adapter* stub1 (struct i2c_client*) ; 
 struct dvb_frontend* stub2 (struct i2c_client*) ; 

struct dvb_frontend *m88ds3103_attach(const struct m88ds3103_config *cfg,
				      struct i2c_adapter *i2c,
				      struct i2c_adapter **tuner_i2c_adapter)
{
	struct i2c_client *client;
	struct i2c_board_info board_info;
	struct m88ds3103_platform_data pdata = {};

	pdata.clk = cfg->clock;
	pdata.i2c_wr_max = cfg->i2c_wr_max;
	pdata.ts_mode = cfg->ts_mode;
	pdata.ts_clk = cfg->ts_clk;
	pdata.ts_clk_pol = cfg->ts_clk_pol;
	pdata.spec_inv = cfg->spec_inv;
	pdata.agc = cfg->agc;
	pdata.agc_inv = cfg->agc_inv;
	pdata.clk_out = cfg->clock_out;
	pdata.envelope_mode = cfg->envelope_mode;
	pdata.lnb_hv_pol = cfg->lnb_hv_pol;
	pdata.lnb_en_pol = cfg->lnb_en_pol;
	pdata.attach_in_use = true;

	memset(&board_info, 0, sizeof(board_info));
	strscpy(board_info.type, "m88ds3103", I2C_NAME_SIZE);
	board_info.addr = cfg->i2c_addr;
	board_info.platform_data = &pdata;
	client = i2c_new_device(i2c, &board_info);
	if (!client || !client->dev.driver)
		return NULL;

	*tuner_i2c_adapter = pdata.get_i2c_adapter(client);
	return pdata.get_dvb_frontend(client);
}