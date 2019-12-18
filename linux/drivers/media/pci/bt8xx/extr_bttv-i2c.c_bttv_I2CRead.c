#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct TYPE_4__ {unsigned char addr; } ;
struct bttv {scalar_t__ i2c_rc; TYPE_1__ c; TYPE_2__ i2c_client; } ;

/* Variables and functions */
 scalar_t__ bttv_verbose ; 
 int i2c_master_recv (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,unsigned char) ; 

int bttv_I2CRead(struct bttv *btv, unsigned char addr, char *probe_for)
{
	unsigned char buffer = 0;

	if (0 != btv->i2c_rc)
		return -1;
	if (bttv_verbose && NULL != probe_for)
		pr_info("%d: i2c: checking for %s @ 0x%02x... ",
			btv->c.nr, probe_for, addr);
	btv->i2c_client.addr = addr >> 1;
	if (1 != i2c_master_recv(&btv->i2c_client, &buffer, 1)) {
		if (NULL != probe_for) {
			if (bttv_verbose)
				pr_cont("not found\n");
		} else
			pr_warn("%d: i2c read 0x%x: error\n",
				btv->c.nr, addr);
		return -1;
	}
	if (bttv_verbose && NULL != probe_for)
		pr_cont("found\n");
	return buffer;
}