#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tveeprom {int dummy; } ;
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_3__ {scalar_t__ decoder; scalar_t__ tuner_type; int /*<<< orphan*/  tuner_i2c_master; } ;
struct cx231xx {size_t model; int tuner_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/ * sd_tuner; int /*<<< orphan*/  v4l2_dev; TYPE_1__ board; int /*<<< orphan*/ * sd_cx25840; int /*<<< orphan*/  tuner_type; } ;
struct TYPE_4__ {int tuner_addr; int /*<<< orphan*/  tuner_type; } ;

/* Variables and functions */
 scalar_t__ CX231XX_AVDECODER ; 
#define  CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx 132 
#define  CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx 131 
#define  CX231XX_BOARD_HAUPPAUGE_935C 130 
#define  CX231XX_BOARD_HAUPPAUGE_955Q 129 
#define  CX231XX_BOARD_HAUPPAUGE_975 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_0 ; 
 int /*<<< orphan*/  I2C_1_MUX_1 ; 
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  core ; 
 TYPE_2__* cx231xx_boards ; 
 int /*<<< orphan*/  cx231xx_config_tuner (struct cx231xx*) ; 
 struct i2c_adapter* cx231xx_get_i2c_adap (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_set_model (struct cx231xx*) ; 
 int /*<<< orphan*/  cx25840_call (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct eeprom*) ; 
 struct eeprom* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_fw ; 
 int /*<<< orphan*/  read_eeprom (struct cx231xx*,struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (struct tveeprom*,int /*<<< orphan*/ ) ; 
 void* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,struct i2c_adapter*,char*,int,int /*<<< orphan*/ *) ; 

void cx231xx_card_setup(struct cx231xx *dev)
{

	cx231xx_set_model(dev);

	dev->tuner_type = cx231xx_boards[dev->model].tuner_type;
	if (cx231xx_boards[dev->model].tuner_addr)
		dev->tuner_addr = cx231xx_boards[dev->model].tuner_addr;

	/* request some modules */
	if (dev->board.decoder == CX231XX_AVDECODER) {
		dev->sd_cx25840 = v4l2_i2c_new_subdev(&dev->v4l2_dev,
					cx231xx_get_i2c_adap(dev, I2C_0),
					"cx25840", 0x88 >> 1, NULL);
		if (dev->sd_cx25840 == NULL)
			dev_err(dev->dev,
				"cx25840 subdev registration failure\n");
		cx25840_call(dev, core, load_fw);

	}

	/* Initialize the tuner */
	if (dev->board.tuner_type != TUNER_ABSENT) {
		struct i2c_adapter *tuner_i2c = cx231xx_get_i2c_adap(dev,
						dev->board.tuner_i2c_master);
		dev->sd_tuner = v4l2_i2c_new_subdev(&dev->v4l2_dev,
						    tuner_i2c,
						    "tuner",
						    dev->tuner_addr, NULL);
		if (dev->sd_tuner == NULL)
			dev_err(dev->dev,
				"tuner subdev registration failure\n");
		else
			cx231xx_config_tuner(dev);
	}

	switch (dev->model) {
	case CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx:
	case CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
	case CX231XX_BOARD_HAUPPAUGE_955Q:
	case CX231XX_BOARD_HAUPPAUGE_935C:
	case CX231XX_BOARD_HAUPPAUGE_975:
		{
			struct eeprom {
				struct tveeprom tvee;
				u8 eeprom[256];
				struct i2c_client client;
			};
			struct eeprom *e = kzalloc(sizeof(*e), GFP_KERNEL);

			if (e == NULL) {
				dev_err(dev->dev,
					"failed to allocate memory to read eeprom\n");
				break;
			}
			e->client.adapter = cx231xx_get_i2c_adap(dev, I2C_1_MUX_1);
			e->client.addr = 0xa0 >> 1;

			read_eeprom(dev, &e->client, e->eeprom, sizeof(e->eeprom));
			tveeprom_hauppauge_analog(&e->tvee, e->eeprom + 0xc0);
			kfree(e);
			break;
		}
	}

}