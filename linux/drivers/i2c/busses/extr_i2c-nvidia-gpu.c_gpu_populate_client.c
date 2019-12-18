#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpu_i2c_dev {int /*<<< orphan*/  ccgx_client; TYPE_1__* gpu_ccgx_ucsi; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int addr; int irq; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ccgx_props ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_new_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int gpu_populate_client(struct gpu_i2c_dev *i2cd, int irq)
{
	i2cd->gpu_ccgx_ucsi = devm_kzalloc(i2cd->dev,
					   sizeof(*i2cd->gpu_ccgx_ucsi),
					   GFP_KERNEL);
	if (!i2cd->gpu_ccgx_ucsi)
		return -ENOMEM;

	strlcpy(i2cd->gpu_ccgx_ucsi->type, "ccgx-ucsi",
		sizeof(i2cd->gpu_ccgx_ucsi->type));
	i2cd->gpu_ccgx_ucsi->addr = 0x8;
	i2cd->gpu_ccgx_ucsi->irq = irq;
	i2cd->gpu_ccgx_ucsi->properties = ccgx_props;
	i2cd->ccgx_client = i2c_new_device(&i2cd->adapter, i2cd->gpu_ccgx_ucsi);
	if (!i2cd->ccgx_client)
		return -ENODEV;

	return 0;
}