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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* reg; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;
struct soc_pcmcia_socket {TYPE_4__* stat; TYPE_3__ vcc; void* gpio_bus_enable; void* gpio_reset; TYPE_2__ socket; } ;
struct device {int dummy; } ;
struct TYPE_8__ {char* name; void* desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get_optional (struct device*,char*) ; 
 char** sa11x0_cf_gpio_names ; 

__attribute__((used)) static int sa11x0_cf_hw_init(struct soc_pcmcia_socket *skt)
{
	struct device *dev = skt->socket.dev.parent;
	int i;

	skt->gpio_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(skt->gpio_reset))
		return PTR_ERR(skt->gpio_reset);

	skt->gpio_bus_enable = devm_gpiod_get_optional(dev, "bus-enable",
						       GPIOD_OUT_HIGH);
	if (IS_ERR(skt->gpio_bus_enable))
		return PTR_ERR(skt->gpio_bus_enable);

	skt->vcc.reg = devm_regulator_get_optional(dev, "vcc");
	if (IS_ERR(skt->vcc.reg))
		return PTR_ERR(skt->vcc.reg);

	if (!skt->vcc.reg)
		dev_warn(dev,
			 "no Vcc regulator provided, ignoring Vcc controls\n");

	for (i = 0; i < ARRAY_SIZE(sa11x0_cf_gpio_names); i++) {
		skt->stat[i].name = sa11x0_cf_gpio_names[i];
		skt->stat[i].desc = devm_gpiod_get_optional(dev,
					sa11x0_cf_gpio_names[i], GPIOD_IN);
		if (IS_ERR(skt->stat[i].desc))
			return PTR_ERR(skt->stat[i].desc);
	}
	return 0;
}