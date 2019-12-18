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
struct iio_channel {int dummy; } ;
struct cpcap_charger_ddata {int /*<<< orphan*/  dev; struct iio_channel** channels; } ;

/* Variables and functions */
 size_t CPCAP_CHARGER_IIO_VBUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int iio_read_channel_processed (struct iio_channel*,int*) ; 

__attribute__((used)) static bool cpcap_charger_vbus_valid(struct cpcap_charger_ddata *ddata)
{
	int error, value = 0;
	struct iio_channel *channel =
		ddata->channels[CPCAP_CHARGER_IIO_VBUS];

	error = iio_read_channel_processed(channel, &value);
	if (error >= 0)
		return value > 3900 ? true : false;

	dev_err(ddata->dev, "error reading VBUS: %i\n", error);

	return false;
}