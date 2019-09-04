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
typedef  int u8 ;
struct gpio_chip {int dummy; } ;
struct f7188x_sio {int /*<<< orphan*/  addr; } ;
struct f7188x_gpio_bank {int /*<<< orphan*/  regbase; TYPE_1__* data; } ;
struct TYPE_2__ {struct f7188x_sio* sio; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIO_LD_GPIO ; 
 int /*<<< orphan*/  gpio_dir (int /*<<< orphan*/ ) ; 
 struct f7188x_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int superio_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_exit (int /*<<< orphan*/ ) ; 
 int superio_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f7188x_gpio_get_direction(struct gpio_chip *chip, unsigned offset)
{
	int err;
	struct f7188x_gpio_bank *bank = gpiochip_get_data(chip);
	struct f7188x_sio *sio = bank->data->sio;
	u8 dir;

	err = superio_enter(sio->addr);
	if (err)
		return err;
	superio_select(sio->addr, SIO_LD_GPIO);

	dir = superio_inb(sio->addr, gpio_dir(bank->regbase));

	superio_exit(sio->addr);

	return !(dir & 1 << offset);
}