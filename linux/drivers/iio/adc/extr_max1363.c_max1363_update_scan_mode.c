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
struct max1363_state {int /*<<< orphan*/  current_mode; int /*<<< orphan*/  chip_info; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct max1363_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max1363_match_mode (unsigned long const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max1363_set_scan_mode (struct max1363_state*) ; 

__attribute__((used)) static int max1363_update_scan_mode(struct iio_dev *indio_dev,
				    const unsigned long *scan_mask)
{
	struct max1363_state *st = iio_priv(indio_dev);

	/*
	 * Need to figure out the current mode based upon the requested
	 * scan mask in iio_dev
	 */
	st->current_mode = max1363_match_mode(scan_mask, st->chip_info);
	if (!st->current_mode)
		return -EINVAL;
	max1363_set_scan_mode(st);
	return 0;
}