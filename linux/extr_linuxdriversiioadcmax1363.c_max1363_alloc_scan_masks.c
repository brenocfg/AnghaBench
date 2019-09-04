#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max1363_state {TYPE_1__* chip_info; } ;
struct iio_dev {unsigned long* available_scan_masks; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  modemask; } ;
struct TYPE_3__ {int num_modes; size_t* mode_list; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX1363_MAX_CHANNELS ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  bitmap_copy (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max1363_state* iio_priv (struct iio_dev*) ; 
 TYPE_2__* max1363_mode_table ; 

__attribute__((used)) static int max1363_alloc_scan_masks(struct iio_dev *indio_dev)
{
	struct max1363_state *st = iio_priv(indio_dev);
	unsigned long *masks;
	int i;

	masks = devm_kzalloc(&indio_dev->dev,
			array3_size(BITS_TO_LONGS(MAX1363_MAX_CHANNELS),
				    sizeof(long),
				    st->chip_info->num_modes + 1),
			GFP_KERNEL);
	if (!masks)
		return -ENOMEM;

	for (i = 0; i < st->chip_info->num_modes; i++)
		bitmap_copy(masks + BITS_TO_LONGS(MAX1363_MAX_CHANNELS)*i,
			    max1363_mode_table[st->chip_info->mode_list[i]]
			    .modemask, MAX1363_MAX_CHANNELS);

	indio_dev->available_scan_masks = masks;

	return 0;
}