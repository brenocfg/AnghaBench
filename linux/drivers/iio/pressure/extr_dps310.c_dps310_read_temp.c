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
struct dps310_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 130 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int IIO_VAL_INT ; 
 int dps310_calculate_temp (struct dps310_data*) ; 
 int dps310_get_temp_precision (struct dps310_data*) ; 
 int dps310_get_temp_samp_freq (struct dps310_data*) ; 
 int dps310_read_temp_raw (struct dps310_data*) ; 

__attribute__((used)) static int dps310_read_temp(struct dps310_data *data, int *val, int *val2,
			    long mask)
{
	int rc;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		rc = dps310_get_temp_samp_freq(data);
		if (rc < 0)
			return rc;

		*val = rc;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_PROCESSED:
		rc = dps310_read_temp_raw(data);
		if (rc)
			return rc;

		rc = dps310_calculate_temp(data);
		if (rc < 0)
			return rc;

		*val = rc;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		rc = dps310_get_temp_precision(data);
		if (rc < 0)
			return rc;

		*val = rc;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}