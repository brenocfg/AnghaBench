#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v3020_platform_data {int /*<<< orphan*/  gpio_io; int /*<<< orphan*/  gpio_rd; int /*<<< orphan*/  gpio_wr; int /*<<< orphan*/  gpio_cs; } ;
struct v3020 {TYPE_1__* gpio; } ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 size_t V3020_CS ; 
 size_t V3020_IO ; 
 size_t V3020_RD ; 
 size_t V3020_WR ; 
 int gpio_request_array (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* v3020_gpio ; 

__attribute__((used)) static int v3020_gpio_map(struct v3020 *chip, struct platform_device *pdev,
			  struct v3020_platform_data *pdata)
{
	int err;

	v3020_gpio[V3020_CS].gpio = pdata->gpio_cs;
	v3020_gpio[V3020_WR].gpio = pdata->gpio_wr;
	v3020_gpio[V3020_RD].gpio = pdata->gpio_rd;
	v3020_gpio[V3020_IO].gpio = pdata->gpio_io;

	err = gpio_request_array(v3020_gpio, ARRAY_SIZE(v3020_gpio));

	if (!err)
		chip->gpio = v3020_gpio;

	return err;
}