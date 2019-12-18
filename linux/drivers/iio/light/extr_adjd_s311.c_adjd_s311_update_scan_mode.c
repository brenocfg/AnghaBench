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
struct iio_dev {int /*<<< orphan*/  scan_bytes; } ;
struct adjd_s311_data {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct adjd_s311_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adjd_s311_update_scan_mode(struct iio_dev *indio_dev,
	const unsigned long *scan_mask)
{
	struct adjd_s311_data *data = iio_priv(indio_dev);

	kfree(data->buffer);
	data->buffer = kmalloc(indio_dev->scan_bytes, GFP_KERNEL);
	if (data->buffer == NULL)
		return -ENOMEM;

	return 0;
}