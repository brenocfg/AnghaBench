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
struct TYPE_2__ {int /*<<< orphan*/  mclk; } ;
struct sii902x {TYPE_1__ audio; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SII902X_TPI_AUDIO_CONFIG_BYTE2_REG ; 
 int /*<<< orphan*/  SII902X_TPI_AUDIO_INTERFACE_DISABLE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sii902x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii902x_audio_shutdown(struct device *dev, void *data)
{
	struct sii902x *sii902x = dev_get_drvdata(dev);

	mutex_lock(&sii902x->mutex);

	regmap_write(sii902x->regmap, SII902X_TPI_AUDIO_CONFIG_BYTE2_REG,
		     SII902X_TPI_AUDIO_INTERFACE_DISABLE);

	mutex_unlock(&sii902x->mutex);

	clk_disable_unprepare(sii902x->audio.mclk);
}