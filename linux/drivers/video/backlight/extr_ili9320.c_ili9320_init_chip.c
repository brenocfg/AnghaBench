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
struct ili9320 {int initialised; int /*<<< orphan*/  dev; int /*<<< orphan*/  platdata; TYPE_1__* client; } ;
struct TYPE_2__ {int (* init ) (struct ili9320*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ili9320_reset (struct ili9320*) ; 
 int stub1 (struct ili9320*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ili9320_init_chip(struct ili9320 *lcd)
{
	int ret;

	ili9320_reset(lcd);

	ret = lcd->client->init(lcd, lcd->platdata);
	if (ret != 0) {
		dev_err(lcd->dev, "failed to initialise display\n");
		return ret;
	}

	lcd->initialised = 1;
	return 0;
}