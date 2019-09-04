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
struct em28xx_i2c_bus {struct em28xx* dev; } ;
struct TYPE_2__ {struct em28xx_i2c_bus* priv; } ;
struct em28xx_dvb {TYPE_1__ adapter; } ;
struct em28xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_stop_urbs (struct em28xx*) ; 

__attribute__((used)) static int em28xx_stop_streaming(struct em28xx_dvb *dvb)
{
	struct em28xx_i2c_bus *i2c_bus = dvb->adapter.priv;
	struct em28xx *dev = i2c_bus->dev;

	em28xx_stop_urbs(dev);

	return 0;
}