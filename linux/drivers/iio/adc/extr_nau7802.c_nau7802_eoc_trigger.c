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
struct nau7802_state {scalar_t__ conversion_count; int /*<<< orphan*/  value_ok; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ NAU7802_MIN_CONVERSIONS ; 
 int NAU7802_PUCTRL_CR_BIT ; 
 int /*<<< orphan*/  NAU7802_REG_PUCTRL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nau7802_state* iio_priv (struct iio_dev*) ; 
 scalar_t__ nau7802_read_conversion (struct nau7802_state*) ; 

__attribute__((used)) static irqreturn_t nau7802_eoc_trigger(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct nau7802_state *st = iio_priv(indio_dev);
	int status;

	status = i2c_smbus_read_byte_data(st->client, NAU7802_REG_PUCTRL);
	if (status < 0)
		return IRQ_HANDLED;

	if (!(status & NAU7802_PUCTRL_CR_BIT))
		return IRQ_NONE;

	if (nau7802_read_conversion(st) < 0)
		return IRQ_HANDLED;

	/*
	 * Because there is actually only one ADC for both channels, we have to
	 * wait for enough conversions to happen before getting a significant
	 * value when changing channels and the values are far apart.
	 */
	if (st->conversion_count < NAU7802_MIN_CONVERSIONS)
		st->conversion_count++;
	if (st->conversion_count >= NAU7802_MIN_CONVERSIONS)
		complete(&st->value_ok);

	return IRQ_HANDLED;
}