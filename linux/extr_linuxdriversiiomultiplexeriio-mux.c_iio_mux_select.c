#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mux_ext_info_cache {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct mux_child {struct mux_ext_info_cache* ext_info_cache; } ;
struct mux {int cached_state; int /*<<< orphan*/  control; int /*<<< orphan*/  parent; struct iio_chan_spec* chan; struct mux_child* child; } ;
struct iio_chan_spec {scalar_t__ channel; TYPE_1__* ext_info; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int iio_write_channel_ext_info (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mux_control_deselect (int /*<<< orphan*/ ) ; 
 int mux_control_select (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int iio_mux_select(struct mux *mux, int idx)
{
	struct mux_child *child = &mux->child[idx];
	struct iio_chan_spec const *chan = &mux->chan[idx];
	int ret;
	int i;

	ret = mux_control_select(mux->control, chan->channel);
	if (ret < 0) {
		mux->cached_state = -1;
		return ret;
	}

	if (mux->cached_state == chan->channel)
		return 0;

	if (chan->ext_info) {
		for (i = 0; chan->ext_info[i].name; ++i) {
			const char *attr = chan->ext_info[i].name;
			struct mux_ext_info_cache *cache;

			cache = &child->ext_info_cache[i];

			if (cache->size < 0)
				continue;

			ret = iio_write_channel_ext_info(mux->parent, attr,
							 cache->data,
							 cache->size);

			if (ret < 0) {
				mux_control_deselect(mux->control);
				mux->cached_state = -1;
				return ret;
			}
		}
	}
	mux->cached_state = chan->channel;

	return 0;
}