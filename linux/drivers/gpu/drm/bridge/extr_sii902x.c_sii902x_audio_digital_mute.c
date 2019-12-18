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
struct sii902x {int /*<<< orphan*/  mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sii902x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sii902x_mute (struct sii902x*,int) ; 

__attribute__((used)) static int sii902x_audio_digital_mute(struct device *dev,
				      void *data, bool enable)
{
	struct sii902x *sii902x = dev_get_drvdata(dev);

	mutex_lock(&sii902x->mutex);

	sii902x_mute(sii902x, enable);

	mutex_unlock(&sii902x->mutex);

	return 0;
}