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
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* adap_to_d (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  au6610_qt1010_config ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qt1010_attach ; 

__attribute__((used)) static int au6610_qt1010_tuner_attach(struct dvb_usb_adapter *adap)
{
	return dvb_attach(qt1010_attach, adap->fe[0],
			&adap_to_d(adap)->i2c_adap,
			&au6610_qt1010_config) == NULL ? -ENODEV : 0;
}