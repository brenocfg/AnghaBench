#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct friio_priv {int /*<<< orphan*/  i2c_client_tuner; } ;
struct dvb_usb_adapter {int dummy; } ;

/* Variables and functions */
 struct friio_priv* adap_to_priv (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int friio_tuner_detach(struct dvb_usb_adapter *adap)
{
	struct friio_priv *priv;

	priv = adap_to_priv(adap);
	dvb_module_release(priv->i2c_client_tuner);
	return 0;
}