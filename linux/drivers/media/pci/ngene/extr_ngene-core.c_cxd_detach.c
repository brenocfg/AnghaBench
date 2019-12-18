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
struct ngene_ci {int /*<<< orphan*/ * en; } ;
struct ngene {TYPE_1__* channel; struct ngene_ci ci; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_ca_en50221_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxd_detach(struct ngene *dev)
{
	struct ngene_ci *ci = &dev->ci;

	dvb_ca_en50221_release(ci->en);

	dvb_module_release(dev->channel[0].i2c_client[0]);
	dev->channel[0].i2c_client[0] = NULL;
	ci->en = NULL;
}