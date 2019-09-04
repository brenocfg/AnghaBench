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
struct TYPE_2__ {int /*<<< orphan*/  callback; } ;
struct tuner {char* name; int standby; double radio_freq; int tv_freq; int mode_mask; int /*<<< orphan*/  type; int /*<<< orphan*/  list; TYPE_1__ fe; int /*<<< orphan*/  config; int /*<<< orphan*/  mode; struct i2c_client* i2c; int /*<<< orphan*/  audmode; int /*<<< orphan*/  sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TUNER_TDA9887 ; 
 int /*<<< orphan*/  TUNER_TEA5761 ; 
 int /*<<< orphan*/  TUNER_TEA5767 ; 
 int T_ANALOG_TV ; 
 int T_RADIO ; 
 int /*<<< orphan*/  UNSET ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int i2c_master_recv (struct i2c_client*,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (struct tuner*) ; 
 struct tuner* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  no_autodetect ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 int /*<<< orphan*/  set_type (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ show_i2c ; 
 int /*<<< orphan*/  tda829x_probe ; 
 int /*<<< orphan*/  tea5761_autodetection ; 
 int /*<<< orphan*/  tea5767_autodetection ; 
 int /*<<< orphan*/  tuner_list ; 
 int /*<<< orphan*/  tuner_lookup (int /*<<< orphan*/ ,struct tuner**,struct tuner**) ; 
 int /*<<< orphan*/  tuner_ops ; 
 int /*<<< orphan*/  tuner_symbol_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tuner_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct tuner *t;
	struct tuner *radio;
	struct tuner *tv;
#ifdef CONFIG_MEDIA_CONTROLLER
	int ret;
#endif

	t = kzalloc(sizeof(struct tuner), GFP_KERNEL);
	if (NULL == t)
		return -ENOMEM;
	v4l2_i2c_subdev_init(&t->sd, client, &tuner_ops);
	t->i2c = client;
	t->name = "(tuner unset)";
	t->type = UNSET;
	t->audmode = V4L2_TUNER_MODE_STEREO;
	t->standby = true;
	t->radio_freq = 87.5 * 16000;	/* Initial freq range */
	t->tv_freq = 400 * 16; /* Sets freq to VHF High - needed for some PLL's to properly start */

	if (show_i2c) {
		unsigned char buffer[16];
		int rc;

		memset(buffer, 0, sizeof(buffer));
		rc = i2c_master_recv(client, buffer, sizeof(buffer));
		if (rc >= 0)
			pr_info("I2C RECV = %*ph\n", rc, buffer);
	}

	/* autodetection code based on the i2c addr */
	if (!no_autodetect) {
		switch (client->addr) {
		case 0x10:
			if (tuner_symbol_probe(tea5761_autodetection,
					       t->i2c->adapter,
					       t->i2c->addr) >= 0) {
				t->type = TUNER_TEA5761;
				t->mode_mask = T_RADIO;
				tuner_lookup(t->i2c->adapter, &radio, &tv);
				if (tv)
					tv->mode_mask &= ~T_RADIO;

				goto register_client;
			}
			kfree(t);
			return -ENODEV;
		case 0x42:
		case 0x43:
		case 0x4a:
		case 0x4b:
			/* If chip is not tda8290, don't register.
			   since it can be tda9887*/
			if (tuner_symbol_probe(tda829x_probe, t->i2c->adapter,
					       t->i2c->addr) >= 0) {
				dprintk("tda829x detected\n");
			} else {
				/* Default is being tda9887 */
				t->type = TUNER_TDA9887;
				t->mode_mask = T_RADIO | T_ANALOG_TV;
				goto register_client;
			}
			break;
		case 0x60:
			if (tuner_symbol_probe(tea5767_autodetection,
					       t->i2c->adapter, t->i2c->addr)
					>= 0) {
				t->type = TUNER_TEA5767;
				t->mode_mask = T_RADIO;
				/* Sets freq to FM range */
				tuner_lookup(t->i2c->adapter, &radio, &tv);
				if (tv)
					tv->mode_mask &= ~T_RADIO;

				goto register_client;
			}
			break;
		}
	}

	/* Initializes only the first TV tuner on this adapter. Why only the
	   first? Because there are some devices (notably the ones with TI
	   tuners) that have more than one i2c address for the *same* device.
	   Experience shows that, except for just one case, the first
	   address is the right one. The exception is a Russian tuner
	   (ACORP_Y878F). So, the desired behavior is just to enable the
	   first found TV tuner. */
	tuner_lookup(t->i2c->adapter, &radio, &tv);
	if (tv == NULL) {
		t->mode_mask = T_ANALOG_TV;
		if (radio == NULL)
			t->mode_mask |= T_RADIO;
		dprintk("Setting mode_mask to 0x%02x\n", t->mode_mask);
	}

	/* Should be just before return */
register_client:
#if defined(CONFIG_MEDIA_CONTROLLER)
	t->sd.entity.name = t->name;
	/*
	 * Handle the special case where the tuner has actually
	 * two stages: the PLL to tune into a frequency and the
	 * IF-PLL demodulator (tda988x).
	 */
	if (t->type == TUNER_TDA9887) {
		t->pad[IF_VID_DEC_PAD_IF_INPUT].flags = MEDIA_PAD_FL_SINK;
		t->pad[IF_VID_DEC_PAD_OUT].flags = MEDIA_PAD_FL_SOURCE;
		ret = media_entity_pads_init(&t->sd.entity,
					     IF_VID_DEC_PAD_NUM_PADS,
					     &t->pad[0]);
		t->sd.entity.function = MEDIA_ENT_F_IF_VID_DECODER;
	} else {
		t->pad[TUNER_PAD_RF_INPUT].flags = MEDIA_PAD_FL_SINK;
		t->pad[TUNER_PAD_OUTPUT].flags = MEDIA_PAD_FL_SOURCE;
		t->pad[TUNER_PAD_AUD_OUT].flags = MEDIA_PAD_FL_SOURCE;
		ret = media_entity_pads_init(&t->sd.entity, TUNER_NUM_PADS,
					     &t->pad[0]);
		t->sd.entity.function = MEDIA_ENT_F_TUNER;
	}

	if (ret < 0) {
		pr_err("failed to initialize media entity!\n");
		kfree(t);
		return ret;
	}
#endif
	/* Sets a default mode */
	if (t->mode_mask & T_ANALOG_TV)
		t->mode = V4L2_TUNER_ANALOG_TV;
	else
		t->mode = V4L2_TUNER_RADIO;
	set_type(client, t->type, t->mode_mask, t->config, t->fe.callback);
	list_add_tail(&t->list, &tuner_list);

	pr_info("Tuner %d found with type(s)%s%s.\n",
		   t->type,
		   t->mode_mask & T_RADIO ? " Radio" : "",
		   t->mode_mask & T_ANALOG_TV ? " TV" : "");
	return 0;
}