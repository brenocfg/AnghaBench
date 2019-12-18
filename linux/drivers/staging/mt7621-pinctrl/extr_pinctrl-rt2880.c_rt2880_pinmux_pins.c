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
typedef  int /*<<< orphan*/  u8 ;
struct rt2880_priv {int func_count; int max_pins; int* gpio; TYPE_3__* desc; TYPE_2__* pads; int /*<<< orphan*/  dev; TYPE_1__** func; } ;
struct pinctrl_pin_desc {int dummy; } ;
struct TYPE_6__ {int npins; TYPE_2__* pins; } ;
struct TYPE_5__ {int number; char* name; } ;
struct TYPE_4__ {int pin_count; int* pins; int pin_first; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 char* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int rt2880_pinmux_pins(struct rt2880_priv *p)
{
	int i, j;

	/*
	 * loop over the functions and initialize the pins array.
	 * also work out the highest pin used.
	 */
	for (i = 0; i < p->func_count; i++) {
		int pin;

		if (!p->func[i]->pin_count)
			continue;

		p->func[i]->pins = devm_kcalloc(p->dev,
						p->func[i]->pin_count,
						sizeof(int),
						GFP_KERNEL);
		for (j = 0; j < p->func[i]->pin_count; j++)
			p->func[i]->pins[j] = p->func[i]->pin_first + j;

		pin = p->func[i]->pin_first + p->func[i]->pin_count;
		if (pin > p->max_pins)
			p->max_pins = pin;
	}

	/* the buffer that tells us which pins are gpio */
	p->gpio = devm_kcalloc(p->dev, p->max_pins, sizeof(u8), GFP_KERNEL);
	/* the pads needed to tell pinctrl about our pins */
	p->pads = devm_kcalloc(p->dev, p->max_pins,
			       sizeof(struct pinctrl_pin_desc), GFP_KERNEL);
	if (!p->pads || !p->gpio) {
		dev_err(p->dev, "Failed to allocate gpio data\n");
		return -ENOMEM;
	}

	memset(p->gpio, 1, sizeof(u8) * p->max_pins);
	for (i = 0; i < p->func_count; i++) {
		if (!p->func[i]->pin_count)
			continue;

		for (j = 0; j < p->func[i]->pin_count; j++)
			p->gpio[p->func[i]->pins[j]] = 0;
	}

	/* pin 0 is always a gpio */
	p->gpio[0] = 1;

	/* set the pads */
	for (i = 0; i < p->max_pins; i++) {
		/* strlen("ioXY") + 1 = 5 */
		char *name = devm_kzalloc(p->dev, 5, GFP_KERNEL);

		if (!name)
			return -ENOMEM;
		snprintf(name, 5, "io%d", i);
		p->pads[i].number = i;
		p->pads[i].name = name;
	}
	p->desc->pins = p->pads;
	p->desc->npins = p->max_pins;

	return 0;
}