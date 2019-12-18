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
struct mipid_device {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_sleep_mode (struct mipid_device*,int) ; 

__attribute__((used)) static void ls041y3_esd_recover(struct mipid_device *md)
{
	dev_err(&md->spi->dev, "performing LCD ESD recovery\n");
	set_sleep_mode(md, 1);
	set_sleep_mode(md, 0);
}