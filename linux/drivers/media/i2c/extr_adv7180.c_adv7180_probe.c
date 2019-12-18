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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  function; } ;
struct v4l2_subdev {int flags; TYPE_1__ entity; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct i2c_client {scalar_t__ irq; TYPE_4__* adapter; int /*<<< orphan*/  dev; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct adv7180_state {scalar_t__ irq; int powered; int /*<<< orphan*/  mutex; void* csi_client; void* vpp_client; TYPE_2__ pad; struct v4l2_subdev sd; scalar_t__ input; struct adv7180_chip_info* chip_info; int /*<<< orphan*/  curr_norm; void* pwdn_gpio; int /*<<< orphan*/  field; struct i2c_client* client; } ;
struct adv7180_chip_info {int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7180_DEFAULT_CSI_I2C_ADDR ; 
 int /*<<< orphan*/  ADV7180_DEFAULT_VPP_I2C_ADDR ; 
 int ADV7180_FLAG_I2P ; 
 int ADV7180_FLAG_MIPI_CSI2 ; 
 int ADV7180_FLAG_RESET_POWERED ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MEDIA_ENT_F_ATV_DECODER ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  V4L2_FIELD_ALTERNATE ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  adv7180_exit_controls (struct adv7180_state*) ; 
 int adv7180_init_controls (struct adv7180_state*) ; 
 int /*<<< orphan*/  adv7180_irq ; 
 int /*<<< orphan*/  adv7180_ops ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct adv7180_state* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct adv7180_state*) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* i2c_new_dummy_device (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unregister_device (void*) ; 
 int init_device (struct adv7180_state*) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_1__*) ; 
 int media_entity_pads_init (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct adv7180_state*) ; 
 int v4l2_async_register_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,int) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7180_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adv7180_state *state;
	struct v4l2_subdev *sd;
	int ret;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
		 client->addr, client->adapter->name);

	state = devm_kzalloc(&client->dev, sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;

	state->client = client;
	state->field = V4L2_FIELD_ALTERNATE;
	state->chip_info = (struct adv7180_chip_info *)id->driver_data;

	state->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "powerdown",
						   GPIOD_OUT_HIGH);
	if (IS_ERR(state->pwdn_gpio)) {
		ret = PTR_ERR(state->pwdn_gpio);
		v4l_err(client, "request for power pin failed: %d\n", ret);
		return ret;
	}

	if (state->chip_info->flags & ADV7180_FLAG_MIPI_CSI2) {
		state->csi_client = i2c_new_dummy_device(client->adapter,
				ADV7180_DEFAULT_CSI_I2C_ADDR);
		if (IS_ERR(state->csi_client))
			return PTR_ERR(state->csi_client);
	}

	if (state->chip_info->flags & ADV7180_FLAG_I2P) {
		state->vpp_client = i2c_new_dummy_device(client->adapter,
				ADV7180_DEFAULT_VPP_I2C_ADDR);
		if (IS_ERR(state->vpp_client)) {
			ret = PTR_ERR(state->vpp_client);
			goto err_unregister_csi_client;
		}
	}

	state->irq = client->irq;
	mutex_init(&state->mutex);
	state->curr_norm = V4L2_STD_NTSC;
	if (state->chip_info->flags & ADV7180_FLAG_RESET_POWERED)
		state->powered = true;
	else
		state->powered = false;
	state->input = 0;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &adv7180_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;

	ret = adv7180_init_controls(state);
	if (ret)
		goto err_unregister_vpp_client;

	state->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_ATV_DECODER;
	ret = media_entity_pads_init(&sd->entity, 1, &state->pad);
	if (ret)
		goto err_free_ctrl;

	ret = init_device(state);
	if (ret)
		goto err_media_entity_cleanup;

	if (state->irq) {
		ret = request_threaded_irq(client->irq, NULL, adv7180_irq,
					   IRQF_ONESHOT | IRQF_TRIGGER_FALLING,
					   KBUILD_MODNAME, state);
		if (ret)
			goto err_media_entity_cleanup;
	}

	ret = v4l2_async_register_subdev(sd);
	if (ret)
		goto err_free_irq;

	return 0;

err_free_irq:
	if (state->irq > 0)
		free_irq(client->irq, state);
err_media_entity_cleanup:
	media_entity_cleanup(&sd->entity);
err_free_ctrl:
	adv7180_exit_controls(state);
err_unregister_vpp_client:
	i2c_unregister_device(state->vpp_client);
err_unregister_csi_client:
	i2c_unregister_device(state->csi_client);
	mutex_destroy(&state->mutex);
	return ret;
}