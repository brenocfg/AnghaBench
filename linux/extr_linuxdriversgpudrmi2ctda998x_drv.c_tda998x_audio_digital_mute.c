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
struct tda998x_priv {int /*<<< orphan*/  audio_mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tda998x_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda998x_audio_mute (struct tda998x_priv*,int) ; 

int tda998x_audio_digital_mute(struct device *dev, void *data, bool enable)
{
	struct tda998x_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->audio_mutex);

	tda998x_audio_mute(priv, enable);

	mutex_unlock(&priv->audio_mutex);
	return 0;
}