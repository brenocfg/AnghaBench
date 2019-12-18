#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* adapter; int /*<<< orphan*/  name; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  owner; TYPE_9__* algo_data; int /*<<< orphan*/ * algo; } ;
struct TYPE_12__ {int nr; TYPE_5__ v4l2_dev; TYPE_4__ i2c_adap; TYPE_2__* pci; } ;
struct TYPE_16__ {int udelay; struct bttv* data; } ;
struct bttv {int use_i2c_hw; int id; scalar_t__ i2c_rc; TYPE_8__ i2c_client; TYPE_3__ c; TYPE_9__ i2c_algo; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I2C_NAME_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bttv_algo ; 
 int /*<<< orphan*/  bttv_bit_setscl (struct bttv*,int) ; 
 int /*<<< orphan*/  bttv_bit_setsda (struct bttv*,int) ; 
 TYPE_9__ bttv_i2c_algo_bit_template ; 
 int /*<<< orphan*/  do_i2c_scan (int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ i2c_add_adapter (TYPE_4__*) ; 
 scalar_t__ i2c_bit_add_bus (TYPE_4__*) ; 
 scalar_t__ i2c_hw ; 
 scalar_t__ i2c_scan ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,TYPE_5__*) ; 
 int i2c_udelay ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

int init_bttv_i2c(struct bttv *btv)
{
	strscpy(btv->i2c_client.name, "bttv internal", I2C_NAME_SIZE);

	if (i2c_hw)
		btv->use_i2c_hw = 1;
	if (btv->use_i2c_hw) {
		/* bt878 */
		strscpy(btv->c.i2c_adap.name, "bt878",
			sizeof(btv->c.i2c_adap.name));
		btv->c.i2c_adap.algo = &bttv_algo;
	} else {
		/* bt848 */
	/* Prevents usage of invalid delay values */
		if (i2c_udelay<5)
			i2c_udelay=5;

		strscpy(btv->c.i2c_adap.name, "bttv",
			sizeof(btv->c.i2c_adap.name));
		btv->i2c_algo = bttv_i2c_algo_bit_template;
		btv->i2c_algo.udelay = i2c_udelay;
		btv->i2c_algo.data = btv;
		btv->c.i2c_adap.algo_data = &btv->i2c_algo;
	}
	btv->c.i2c_adap.owner = THIS_MODULE;

	btv->c.i2c_adap.dev.parent = &btv->c.pci->dev;
	snprintf(btv->c.i2c_adap.name, sizeof(btv->c.i2c_adap.name),
		 "bt%d #%d [%s]", btv->id, btv->c.nr,
		 btv->use_i2c_hw ? "hw" : "sw");

	i2c_set_adapdata(&btv->c.i2c_adap, &btv->c.v4l2_dev);
	btv->i2c_client.adapter = &btv->c.i2c_adap;


	if (btv->use_i2c_hw) {
		btv->i2c_rc = i2c_add_adapter(&btv->c.i2c_adap);
	} else {
		bttv_bit_setscl(btv,1);
		bttv_bit_setsda(btv,1);
		btv->i2c_rc = i2c_bit_add_bus(&btv->c.i2c_adap);
	}
	if (0 == btv->i2c_rc && i2c_scan)
		do_i2c_scan(btv->c.v4l2_dev.name, &btv->i2c_client);

	return btv->i2c_rc;
}