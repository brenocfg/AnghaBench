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
struct iio_dev {int /*<<< orphan*/  masklength; scalar_t__ available_scan_masks; } ;
struct iio_buffer {unsigned long* scan_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  bitmap_copy (unsigned long*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_free (unsigned long*) ; 
 unsigned long* iio_scan_mask_match (scalar_t__,int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  iio_validate_scan_mask (struct iio_dev*,unsigned long*) ; 
 unsigned long* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static int iio_scan_mask_set(struct iio_dev *indio_dev,
		      struct iio_buffer *buffer, int bit)
{
	const unsigned long *mask;
	unsigned long *trialmask;

	trialmask = kcalloc(BITS_TO_LONGS(indio_dev->masklength),
			    sizeof(*trialmask), GFP_KERNEL);
	if (trialmask == NULL)
		return -ENOMEM;
	if (!indio_dev->masklength) {
		WARN(1, "Trying to set scanmask prior to registering buffer\n");
		goto err_invalid_mask;
	}
	bitmap_copy(trialmask, buffer->scan_mask, indio_dev->masklength);
	set_bit(bit, trialmask);

	if (!iio_validate_scan_mask(indio_dev, trialmask))
		goto err_invalid_mask;

	if (indio_dev->available_scan_masks) {
		mask = iio_scan_mask_match(indio_dev->available_scan_masks,
					   indio_dev->masklength,
					   trialmask, false);
		if (!mask)
			goto err_invalid_mask;
	}
	bitmap_copy(buffer->scan_mask, trialmask, indio_dev->masklength);

	bitmap_free(trialmask);

	return 0;

err_invalid_mask:
	bitmap_free(trialmask);
	return -EINVAL;
}