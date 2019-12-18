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
struct sii9234 {int /*<<< orphan*/ * client; } ;

/* Variables and functions */
 size_t I2C_CBUS ; 
 size_t I2C_HDMI ; 
 size_t I2C_TPI ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii9234_deinit_resources(struct sii9234 *ctx)
{
	i2c_unregister_device(ctx->client[I2C_CBUS]);
	i2c_unregister_device(ctx->client[I2C_HDMI]);
	i2c_unregister_device(ctx->client[I2C_TPI]);
}