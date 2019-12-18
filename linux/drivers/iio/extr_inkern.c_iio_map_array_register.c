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
struct iio_map_internal {int /*<<< orphan*/  l; struct iio_dev* indio_dev; struct iio_map* map; } ;
struct iio_map {int /*<<< orphan*/ * consumer_dev_name; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iio_map_list ; 
 int /*<<< orphan*/  iio_map_list_lock ; 
 struct iio_map_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iio_map_array_register(struct iio_dev *indio_dev, struct iio_map *maps)
{
	int i = 0, ret = 0;
	struct iio_map_internal *mapi;

	if (maps == NULL)
		return 0;

	mutex_lock(&iio_map_list_lock);
	while (maps[i].consumer_dev_name != NULL) {
		mapi = kzalloc(sizeof(*mapi), GFP_KERNEL);
		if (mapi == NULL) {
			ret = -ENOMEM;
			goto error_ret;
		}
		mapi->map = &maps[i];
		mapi->indio_dev = indio_dev;
		list_add_tail(&mapi->l, &iio_map_list);
		i++;
	}
error_ret:
	mutex_unlock(&iio_map_list_lock);

	return ret;
}