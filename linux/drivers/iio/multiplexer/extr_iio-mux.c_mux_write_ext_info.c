#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mux {TYPE_4__* child; TYPE_2__* ext_info; int /*<<< orphan*/  parent; struct iio_chan_spec const* chan; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct iio_chan_spec {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_8__ {TYPE_3__* ext_info_cache; } ;
struct TYPE_7__ {char* data; size_t size; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  devm_kfree (struct device*,char*) ; 
 char* devm_kmemdup (struct device*,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_mux_deselect (struct mux*) ; 
 scalar_t__ iio_mux_select (struct mux*,int) ; 
 struct mux* iio_priv (struct iio_dev*) ; 
 scalar_t__ iio_write_channel_ext_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static ssize_t mux_write_ext_info(struct iio_dev *indio_dev, uintptr_t private,
				  struct iio_chan_spec const *chan,
				  const char *buf, size_t len)
{
	struct device *dev = indio_dev->dev.parent;
	struct mux *mux = iio_priv(indio_dev);
	int idx = chan - mux->chan;
	char *new;
	ssize_t ret;

	if (len >= PAGE_SIZE)
		return -EINVAL;

	ret = iio_mux_select(mux, idx);
	if (ret < 0)
		return ret;

	new = devm_kmemdup(dev, buf, len + 1, GFP_KERNEL);
	if (!new) {
		iio_mux_deselect(mux);
		return -ENOMEM;
	}

	new[len] = 0;

	ret = iio_write_channel_ext_info(mux->parent,
					 mux->ext_info[private].name,
					 buf, len);
	if (ret < 0) {
		iio_mux_deselect(mux);
		devm_kfree(dev, new);
		return ret;
	}

	devm_kfree(dev, mux->child[idx].ext_info_cache[private].data);
	mux->child[idx].ext_info_cache[private].data = new;
	mux->child[idx].ext_info_cache[private].size = len;

	iio_mux_deselect(mux);

	return ret;
}