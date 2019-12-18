#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct twl4030_audio {int /*<<< orphan*/  mutex; TYPE_1__* resource; } ;
typedef  enum twl4030_audio_res { ____Placeholder_twl4030_audio_res } twl4030_audio_res ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  request_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int TWL4030_AUDIO_RES_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct twl4030_audio* platform_get_drvdata (TYPE_2__*) ; 
 TYPE_2__* twl4030_audio_dev ; 
 int twl4030_audio_get_resource (int) ; 
 int twl4030_audio_set_resource (int,int) ; 

int twl4030_audio_enable_resource(enum twl4030_audio_res id)
{
	struct twl4030_audio *audio = platform_get_drvdata(twl4030_audio_dev);
	int val;

	if (id >= TWL4030_AUDIO_RES_MAX) {
		dev_err(&twl4030_audio_dev->dev,
				"Invalid resource ID (%u)\n", id);
		return -EINVAL;
	}

	mutex_lock(&audio->mutex);
	if (!audio->resource[id].request_count)
		/* Resource was disabled, enable it */
		val = twl4030_audio_set_resource(id, 1);
	else
		val = twl4030_audio_get_resource(id);

	audio->resource[id].request_count++;
	mutex_unlock(&audio->mutex);

	return val;
}