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
struct TYPE_2__ {int addr; } ;
struct bttv {scalar_t__ i2c_rc; TYPE_1__ i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tveeprom_read (TYPE_1__*,unsigned char*,int) ; 

void bttv_readee(struct bttv *btv, unsigned char *eedata, int addr)
{
	memset(eedata, 0, 256);
	if (0 != btv->i2c_rc)
		return;
	btv->i2c_client.addr = addr >> 1;
	tveeprom_read(&btv->i2c_client, eedata, 256);
}