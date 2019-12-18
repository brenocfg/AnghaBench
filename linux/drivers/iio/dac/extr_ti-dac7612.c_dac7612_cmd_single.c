#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct dac7612 {int* data; int* cache; int /*<<< orphan*/  loaddacs; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DAC7612_ADDRESS ; 
 int /*<<< orphan*/  DAC7612_START ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int spi_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int dac7612_cmd_single(struct dac7612 *priv, int channel, u16 val)
{
	int ret;

	priv->data[0] = BIT(DAC7612_START) | (channel << DAC7612_ADDRESS);
	priv->data[0] |= val >> 8;
	priv->data[1] = val & 0xff;

	priv->cache[channel] = val;

	ret = spi_write(priv->spi, priv->data, sizeof(priv->data));
	if (ret)
		return ret;

	gpiod_set_value(priv->loaddacs, 1);
	gpiod_set_value(priv->loaddacs, 0);

	return 0;
}