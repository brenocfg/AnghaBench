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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adp5588_kpad_platform_data {int unlock_key1; int unlock_key2; int gpimapsize; TYPE_1__* gpimap; scalar_t__ en_keylock; int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; struct adp5588_gpio_platform_data* gpio_data; } ;
struct adp5588_gpio_platform_data {int pullup_dis_mask; } ;
struct TYPE_2__ {unsigned short pin; } ;

/* Variables and functions */
 int ADP5588_BANK (int /*<<< orphan*/ ) ; 
 int ADP5588_CMP1_INT ; 
 int ADP5588_CMP2_INT ; 
 int ADP5588_GPI_INT ; 
 int ADP5588_INT_CFG ; 
 int ADP5588_KE_IEN ; 
 int ADP5588_KE_INT ; 
 int ADP5588_K_LCK_EN ; 
 int ADP5588_K_LCK_INT ; 
 int /*<<< orphan*/  ADP5588_MAXGPIO ; 
 int ADP5588_OVR_FLOW_IEN ; 
 int ADP5588_OVR_FLOW_INT ; 
 scalar_t__ CFG ; 
 scalar_t__ GPIO_PULL1 ; 
 scalar_t__ GPI_EM1 ; 
 scalar_t__ GPI_EM2 ; 
 scalar_t__ GPI_EM3 ; 
 unsigned short GPI_PIN_COL_BASE ; 
 unsigned short GPI_PIN_ROW_BASE ; 
 unsigned short GPI_PIN_ROW_END ; 
 scalar_t__ INT_STAT ; 
 int KEYP_MAX_EVENT ; 
 scalar_t__ KEY_LCK_EC_STAT ; 
 scalar_t__ KP_GPIO1 ; 
 scalar_t__ KP_GPIO2 ; 
 scalar_t__ KP_GPIO3 ; 
 int KP_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Key_EVENTA ; 
 scalar_t__ UNLOCK1 ; 
 scalar_t__ UNLOCK2 ; 
 int adp5588_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int adp5588_write (struct i2c_client*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct adp5588_kpad_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5588_setup(struct i2c_client *client)
{
	const struct adp5588_kpad_platform_data *pdata =
			dev_get_platdata(&client->dev);
	const struct adp5588_gpio_platform_data *gpio_data = pdata->gpio_data;
	int i, ret;
	unsigned char evt_mode1 = 0, evt_mode2 = 0, evt_mode3 = 0;

	ret = adp5588_write(client, KP_GPIO1, KP_SEL(pdata->rows));
	ret |= adp5588_write(client, KP_GPIO2, KP_SEL(pdata->cols) & 0xFF);
	ret |= adp5588_write(client, KP_GPIO3, KP_SEL(pdata->cols) >> 8);

	if (pdata->en_keylock) {
		ret |= adp5588_write(client, UNLOCK1, pdata->unlock_key1);
		ret |= adp5588_write(client, UNLOCK2, pdata->unlock_key2);
		ret |= adp5588_write(client, KEY_LCK_EC_STAT, ADP5588_K_LCK_EN);
	}

	for (i = 0; i < KEYP_MAX_EVENT; i++)
		ret |= adp5588_read(client, Key_EVENTA);

	for (i = 0; i < pdata->gpimapsize; i++) {
		unsigned short pin = pdata->gpimap[i].pin;

		if (pin <= GPI_PIN_ROW_END) {
			evt_mode1 |= (1 << (pin - GPI_PIN_ROW_BASE));
		} else {
			evt_mode2 |= ((1 << (pin - GPI_PIN_COL_BASE)) & 0xFF);
			evt_mode3 |= ((1 << (pin - GPI_PIN_COL_BASE)) >> 8);
		}
	}

	if (pdata->gpimapsize) {
		ret |= adp5588_write(client, GPI_EM1, evt_mode1);
		ret |= adp5588_write(client, GPI_EM2, evt_mode2);
		ret |= adp5588_write(client, GPI_EM3, evt_mode3);
	}

	if (gpio_data) {
		for (i = 0; i <= ADP5588_BANK(ADP5588_MAXGPIO); i++) {
			int pull_mask = gpio_data->pullup_dis_mask;

			ret |= adp5588_write(client, GPIO_PULL1 + i,
				(pull_mask >> (8 * i)) & 0xFF);
		}
	}

	ret |= adp5588_write(client, INT_STAT,
				ADP5588_CMP2_INT | ADP5588_CMP1_INT |
				ADP5588_OVR_FLOW_INT | ADP5588_K_LCK_INT |
				ADP5588_GPI_INT | ADP5588_KE_INT); /* Status is W1C */

	ret |= adp5588_write(client, CFG, ADP5588_INT_CFG |
					  ADP5588_OVR_FLOW_IEN |
					  ADP5588_KE_IEN);

	if (ret < 0) {
		dev_err(&client->dev, "Write Error\n");
		return ret;
	}

	return 0;
}