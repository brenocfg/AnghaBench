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
struct dvb_usb_adapter {TYPE_2__* fe_adap; TYPE_1__* dev; } ;
struct digitv_state {int is_nxt6000; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; struct digitv_state* priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  digitv_mt352_config ; 
 int /*<<< orphan*/  digitv_nxt6000_config ; 
 void* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt352_attach ; 
 int /*<<< orphan*/  nxt6000_attach ; 

__attribute__((used)) static int digitv_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct digitv_state *st = adap->dev->priv;

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &digitv_mt352_config,
					 &adap->dev->i2c_adap);
	if ((adap->fe_adap[0].fe) != NULL) {
		st->is_nxt6000 = 0;
		return 0;
	}
	adap->fe_adap[0].fe = dvb_attach(nxt6000_attach,
					 &digitv_nxt6000_config,
					 &adap->dev->i2c_adap);
	if ((adap->fe_adap[0].fe) != NULL) {
		st->is_nxt6000 = 1;
		return 0;
	}
	return -EIO;
}