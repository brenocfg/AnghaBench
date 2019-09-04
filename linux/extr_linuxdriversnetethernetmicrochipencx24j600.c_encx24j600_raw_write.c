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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct encx24j600_priv {TYPE_1__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_encx24j600_spi_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int encx24j600_raw_write(struct encx24j600_priv *priv, u8 reg,
				const u8 *data, size_t count)
{
	int ret;

	mutex_lock(&priv->ctx.mutex);
	ret = regmap_encx24j600_spi_write(&priv->ctx, reg, data, count);
	mutex_unlock(&priv->ctx.mutex);

	return ret;
}