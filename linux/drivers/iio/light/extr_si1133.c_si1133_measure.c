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
typedef  int /*<<< orphan*/  u8 ;
struct si1133_data {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI1133_REG_HOSTOUT (int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int si1133_bulk_read (struct si1133_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int si1133_set_adcmux (struct si1133_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si1133_set_chlist (struct si1133_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1133_measure(struct si1133_data *data,
			  struct iio_chan_spec const *chan,
			  int *val)
{
	int err;

	__be16 resp;

	err = si1133_set_adcmux(data, 0, chan->channel);
	if (err)
		return err;

	/* Deactivate lux measurements if they were active */
	err = si1133_set_chlist(data, BIT(0));
	if (err)
		return err;

	err = si1133_bulk_read(data, SI1133_REG_HOSTOUT(0), sizeof(resp),
			       (u8 *)&resp);
	if (err)
		return err;

	*val = be16_to_cpu(resp);

	return err;
}