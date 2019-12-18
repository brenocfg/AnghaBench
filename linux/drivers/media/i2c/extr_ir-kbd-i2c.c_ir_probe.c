#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct rc_dev {char const* device_name; char* map_name; int allowed_protocols; int /*<<< orphan*/  s_tx_duty_cycle; int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  tx_ir; scalar_t__ driver_name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct IR_i2c* priv; TYPE_2__ dev; int /*<<< orphan*/  input_phys; TYPE_1__ input_id; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_9__ {struct IR_i2c_init_data* platform_data; } ;
struct i2c_client {unsigned short addr; TYPE_3__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {TYPE_3__ dev; } ;
struct IR_i2c_init_data {char* ir_codes; char* name; int type; int internal_get_key_func; void* get_key; scalar_t__ polling_interval; struct rc_dev* rc_dev; } ;
struct IR_i2c {char* ir_codes; int carrier; int duty_cycle; int /*<<< orphan*/  tx_c; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  phys; void* get_key; struct rc_dev* rc; scalar_t__ polling_interval; struct i2c_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 scalar_t__ DEFAULT_POLLING_INTERVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FLAG_HDPVR ; 
 int FLAG_TX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  IR_KBD_GET_KEY_AVERMEDIA_CARDBUS 134 
#define  IR_KBD_GET_KEY_CUSTOM 133 
#define  IR_KBD_GET_KEY_FUSIONHDTV 132 
#define  IR_KBD_GET_KEY_HAUP 131 
#define  IR_KBD_GET_KEY_HAUP_XVR 130 
#define  IR_KBD_GET_KEY_KNC1 129 
#define  IR_KBD_GET_KEY_PIXELVIEW 128 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ KBUILD_MODNAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC_DRIVER_SCANCODE ; 
 char* RC_MAP_AVERMEDIA_CARDBUS ; 
 char* RC_MAP_AVERMEDIA_M733A_RM_K6 ; 
 char* RC_MAP_EMPTY ; 
 char* RC_MAP_FUSIONHDTV_MCE ; 
 char* RC_MAP_HAUPPAUGE ; 
 int RC_PROTO_BIT_OTHER ; 
 int RC_PROTO_BIT_RC5 ; 
 int RC_PROTO_BIT_RC6_6A_32 ; 
 int RC_PROTO_BIT_RC6_MCE ; 
 int RC_PROTO_BIT_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 char* dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,unsigned short) ; 
 struct IR_i2c* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_hdpvr ; 
 void* get_key_avermedia_cardbus ; 
 void* get_key_fusionhdtv ; 
 void* get_key_haup ; 
 void* get_key_haup_xvr ; 
 void* get_key_knc1 ; 
 void* get_key_pixelview ; 
 int /*<<< orphan*/  i2c_new_dummy_device (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct IR_i2c*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_close ; 
 int /*<<< orphan*/  ir_open ; 
 int /*<<< orphan*/  ir_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  zilog_init (struct IR_i2c*) ; 
 int /*<<< orphan*/  zilog_tx ; 
 int /*<<< orphan*/  zilog_tx_carrier ; 
 int /*<<< orphan*/  zilog_tx_duty_cycle ; 

__attribute__((used)) static int ir_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	char *ir_codes = NULL;
	const char *name = NULL;
	u64 rc_proto = RC_PROTO_BIT_UNKNOWN;
	struct IR_i2c *ir;
	struct rc_dev *rc = NULL;
	struct i2c_adapter *adap = client->adapter;
	unsigned short addr = client->addr;
	bool probe_tx = (id->driver_data & FLAG_TX) != 0;
	int err;

	if ((id->driver_data & FLAG_HDPVR) && !enable_hdpvr) {
		dev_err(&client->dev, "IR for HDPVR is known to cause problems during recording, use enable_hdpvr modparam to enable\n");
		return -ENODEV;
	}

	ir = devm_kzalloc(&client->dev, sizeof(*ir), GFP_KERNEL);
	if (!ir)
		return -ENOMEM;

	ir->c = client;
	ir->polling_interval = DEFAULT_POLLING_INTERVAL;
	i2c_set_clientdata(client, ir);

	switch(addr) {
	case 0x64:
		name        = "Pixelview";
		ir->get_key = get_key_pixelview;
		rc_proto    = RC_PROTO_BIT_OTHER;
		ir_codes    = RC_MAP_EMPTY;
		break;
	case 0x18:
	case 0x1f:
	case 0x1a:
		name        = "Hauppauge";
		ir->get_key = get_key_haup;
		rc_proto    = RC_PROTO_BIT_RC5;
		ir_codes    = RC_MAP_HAUPPAUGE;
		break;
	case 0x30:
		name        = "KNC One";
		ir->get_key = get_key_knc1;
		rc_proto    = RC_PROTO_BIT_OTHER;
		ir_codes    = RC_MAP_EMPTY;
		break;
	case 0x6b:
		name        = "FusionHDTV";
		ir->get_key = get_key_fusionhdtv;
		rc_proto    = RC_PROTO_BIT_UNKNOWN;
		ir_codes    = RC_MAP_FUSIONHDTV_MCE;
		break;
	case 0x40:
		name        = "AVerMedia Cardbus remote";
		ir->get_key = get_key_avermedia_cardbus;
		rc_proto    = RC_PROTO_BIT_OTHER;
		ir_codes    = RC_MAP_AVERMEDIA_CARDBUS;
		break;
	case 0x41:
		name        = "AVerMedia EM78P153";
		ir->get_key = get_key_avermedia_cardbus;
		rc_proto    = RC_PROTO_BIT_OTHER;
		/* RM-KV remote, seems to be same as RM-K6 */
		ir_codes    = RC_MAP_AVERMEDIA_M733A_RM_K6;
		break;
	case 0x71:
		name        = "Hauppauge/Zilog Z8";
		ir->get_key = get_key_haup_xvr;
		rc_proto    = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC6_MCE |
							RC_PROTO_BIT_RC6_6A_32;
		ir_codes    = RC_MAP_HAUPPAUGE;
		probe_tx = true;
		break;
	}

	/* Let the caller override settings */
	if (client->dev.platform_data) {
		const struct IR_i2c_init_data *init_data =
						client->dev.platform_data;

		ir_codes = init_data->ir_codes;
		rc = init_data->rc_dev;

		name = init_data->name;
		if (init_data->type)
			rc_proto = init_data->type;

		if (init_data->polling_interval)
			ir->polling_interval = init_data->polling_interval;

		switch (init_data->internal_get_key_func) {
		case IR_KBD_GET_KEY_CUSTOM:
			/* The bridge driver provided us its own function */
			ir->get_key = init_data->get_key;
			break;
		case IR_KBD_GET_KEY_PIXELVIEW:
			ir->get_key = get_key_pixelview;
			break;
		case IR_KBD_GET_KEY_HAUP:
			ir->get_key = get_key_haup;
			break;
		case IR_KBD_GET_KEY_KNC1:
			ir->get_key = get_key_knc1;
			break;
		case IR_KBD_GET_KEY_FUSIONHDTV:
			ir->get_key = get_key_fusionhdtv;
			break;
		case IR_KBD_GET_KEY_HAUP_XVR:
			ir->get_key = get_key_haup_xvr;
			break;
		case IR_KBD_GET_KEY_AVERMEDIA_CARDBUS:
			ir->get_key = get_key_avermedia_cardbus;
			break;
		}
	}

	if (!rc) {
		/*
		 * If platform_data doesn't specify rc_dev, initialize it
		 * internally
		 */
		rc = rc_allocate_device(RC_DRIVER_SCANCODE);
		if (!rc)
			return -ENOMEM;
	}
	ir->rc = rc;

	/* Make sure we are all setup before going on */
	if (!name || !ir->get_key || !rc_proto || !ir_codes) {
		dev_warn(&client->dev, "Unsupported device at address 0x%02x\n",
			 addr);
		err = -ENODEV;
		goto err_out_free;
	}

	ir->ir_codes = ir_codes;

	snprintf(ir->phys, sizeof(ir->phys), "%s/%s", dev_name(&adap->dev),
		 dev_name(&client->dev));

	/*
	 * Initialize input_dev fields
	 * It doesn't make sense to allow overriding them via platform_data
	 */
	rc->input_id.bustype = BUS_I2C;
	rc->input_phys       = ir->phys;
	rc->device_name	     = name;
	rc->dev.parent       = &client->dev;
	rc->priv             = ir;
	rc->open             = ir_open;
	rc->close            = ir_close;

	/*
	 * Initialize the other fields of rc_dev
	 */
	rc->map_name       = ir->ir_codes;
	rc->allowed_protocols = rc_proto;
	if (!rc->driver_name)
		rc->driver_name = KBUILD_MODNAME;

	mutex_init(&ir->lock);

	INIT_DELAYED_WORK(&ir->work, ir_work);

	if (probe_tx) {
		ir->tx_c = i2c_new_dummy_device(client->adapter, 0x70);
		if (IS_ERR(ir->tx_c)) {
			dev_err(&client->dev, "failed to setup tx i2c address");
			err = PTR_ERR(ir->tx_c);
			goto err_out_free;
		} else if (!zilog_init(ir)) {
			ir->carrier = 38000;
			ir->duty_cycle = 40;
			rc->tx_ir = zilog_tx;
			rc->s_tx_carrier = zilog_tx_carrier;
			rc->s_tx_duty_cycle = zilog_tx_duty_cycle;
		}
	}

	err = rc_register_device(rc);
	if (err)
		goto err_out_free;

	return 0;

 err_out_free:
	if (!IS_ERR(ir->tx_c))
		i2c_unregister_device(ir->tx_c);

	/* Only frees rc if it were allocated internally */
	rc_free_device(rc);
	return err;
}