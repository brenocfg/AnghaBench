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
struct dvb_usb_adapter {int /*<<< orphan*/ ** fe; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__* adap_to_d (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl861_zl10353_config ; 
 int /*<<< orphan*/  zl10353_attach ; 

__attribute__((used)) static int gl861_frontend_attach(struct dvb_usb_adapter *adap)
{

	adap->fe[0] = dvb_attach(zl10353_attach, &gl861_zl10353_config,
		&adap_to_d(adap)->i2c_adap);
	if (adap->fe[0] == NULL)
		return -EIO;

	return 0;
}