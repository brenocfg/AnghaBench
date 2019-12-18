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
struct TYPE_2__ {scalar_t__ ena_ap; } ;
struct tda998x_priv {int /*<<< orphan*/  audio_mutex; TYPE_1__ audio; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ENA_AP ; 
 struct tda998x_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tda998x_audio_shutdown(struct device *dev, void *data)
{
	struct tda998x_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->audio_mutex);

	reg_write(priv, REG_ENA_AP, 0);
	priv->audio.ena_ap = 0;

	mutex_unlock(&priv->audio_mutex);
}