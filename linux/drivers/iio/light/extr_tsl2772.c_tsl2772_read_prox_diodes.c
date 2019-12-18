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
typedef  int u32 ;
struct tsl2772_chip {TYPE_1__* client; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int TSL2772_DIODE0 ; 
 int TSL2772_DIODE1 ; 
 int TSL2772_MAX_PROX_LEDS ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int of_property_count_u32_elems (struct device_node*,char*) ; 
 int of_property_read_u32_array (struct device_node*,char*,int*,int) ; 

__attribute__((used)) static int tsl2772_read_prox_diodes(struct tsl2772_chip *chip)
{
	struct device_node *of_node = chip->client->dev.of_node;
	int i, ret, num_leds, prox_diode_mask;
	u32 leds[TSL2772_MAX_PROX_LEDS];

	ret = of_property_count_u32_elems(of_node, "amstaos,proximity-diodes");
	if (ret < 0)
		return ret;

	num_leds = ret;
	if (num_leds > TSL2772_MAX_PROX_LEDS)
		num_leds = TSL2772_MAX_PROX_LEDS;

	ret = of_property_read_u32_array(of_node, "amstaos,proximity-diodes",
					 leds, num_leds);
	if (ret < 0) {
		dev_err(&chip->client->dev,
			"Invalid value for amstaos,proximity-diodes: %d.\n",
			ret);
		return ret;
	}

	prox_diode_mask = 0;
	for (i = 0; i < num_leds; i++) {
		if (leds[i] == 0)
			prox_diode_mask |= TSL2772_DIODE0;
		else if (leds[i] == 1)
			prox_diode_mask |= TSL2772_DIODE1;
		else {
			dev_err(&chip->client->dev,
				"Invalid value %d in amstaos,proximity-diodes.\n",
				leds[i]);
			return -EINVAL;
		}
	}

	return 0;
}