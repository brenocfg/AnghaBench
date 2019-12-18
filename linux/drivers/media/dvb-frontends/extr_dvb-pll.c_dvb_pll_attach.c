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
typedef  scalar_t__ u8 ;
struct i2c_msg {int addr; int len; scalar_t__* buf; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct dvb_pll_priv {int pll_i2c_address; int nr; struct dvb_pll_desc const* pll_desc; struct i2c_adapter* i2c; } ;
struct dvb_pll_desc {int /*<<< orphan*/  name; int /*<<< orphan*/  sleepdata; int /*<<< orphan*/  initdata; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_4__ {int /*<<< orphan*/  frequency_max_hz; int /*<<< orphan*/  frequency_min_hz; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sleep; int /*<<< orphan*/ * init; TYPE_1__ info; } ;
struct TYPE_5__ {TYPE_3__ tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {struct dvb_pll_priv* tuner_priv; TYPE_2__ ops; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct dvb_pll_desc**) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DVB_PLL_MAX ; 
 unsigned int DVB_PLL_UNDEFINED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dprintk (char*,size_t,...) ; 
 int /*<<< orphan*/  dvb_pll_tuner_ops ; 
 int /*<<< orphan*/  i2c_adapter_id (struct i2c_adapter*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 unsigned int* id ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct dvb_pll_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pll_ida ; 
 struct dvb_pll_desc** pll_list ; 
 int /*<<< orphan*/  pr_cont (char*,unsigned int,int,...) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

struct dvb_frontend *dvb_pll_attach(struct dvb_frontend *fe, int pll_addr,
				    struct i2c_adapter *i2c,
				    unsigned int pll_desc_id)
{
	u8 *b1;
	struct i2c_msg msg = { .addr = pll_addr, .flags = I2C_M_RD, .len = 1 };
	struct dvb_pll_priv *priv = NULL;
	int ret;
	const struct dvb_pll_desc *desc;
	int nr;

	b1 = kmalloc(1, GFP_KERNEL);
	if (!b1)
		return NULL;

	b1[0] = 0;
	msg.buf = b1;

	nr = ida_simple_get(&pll_ida, 0, DVB_PLL_MAX, GFP_KERNEL);
	if (nr < 0) {
		kfree(b1);
		return NULL;
	}

	if (id[nr] > DVB_PLL_UNDEFINED && id[nr] < ARRAY_SIZE(pll_list))
		pll_desc_id = id[nr];

	BUG_ON(pll_desc_id < 1 || pll_desc_id >= ARRAY_SIZE(pll_list));

	desc = pll_list[pll_desc_id];

	if (i2c != NULL) {
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = i2c_transfer (i2c, &msg, 1);
		if (ret != 1)
			goto out;
		if (fe->ops.i2c_gate_ctrl)
			     fe->ops.i2c_gate_ctrl(fe, 0);
	}

	priv = kzalloc(sizeof(struct dvb_pll_priv), GFP_KERNEL);
	if (!priv)
		goto out;

	priv->pll_i2c_address = pll_addr;
	priv->i2c = i2c;
	priv->pll_desc = desc;
	priv->nr = nr;

	memcpy(&fe->ops.tuner_ops, &dvb_pll_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	strscpy(fe->ops.tuner_ops.info.name, desc->name,
		sizeof(fe->ops.tuner_ops.info.name));

	fe->ops.tuner_ops.info.frequency_min_hz = desc->min;
	fe->ops.tuner_ops.info.frequency_max_hz = desc->max;

	dprintk("%s tuner, frequency range: %u...%u\n",
		desc->name, desc->min, desc->max);

	if (!desc->initdata)
		fe->ops.tuner_ops.init = NULL;
	if (!desc->sleepdata)
		fe->ops.tuner_ops.sleep = NULL;

	fe->tuner_priv = priv;

	if ((debug) || (id[priv->nr] == pll_desc_id)) {
		dprintk("dvb-pll[%d]", priv->nr);
		if (i2c != NULL)
			pr_cont(" %d-%04x", i2c_adapter_id(i2c), pll_addr);
		pr_cont(": id# %d (%s) attached, %s\n", pll_desc_id, desc->name,
		       id[priv->nr] == pll_desc_id ?
				"insmod option" : "autodetected");
	}

	kfree(b1);

	return fe;
out:
	kfree(b1);
	ida_simple_remove(&pll_ida, nr);

	return NULL;
}