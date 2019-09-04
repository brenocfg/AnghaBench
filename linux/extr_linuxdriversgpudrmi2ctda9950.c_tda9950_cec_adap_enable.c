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
struct tda9950_priv {int dummy; } ;
struct cec_adapter {struct tda9950_priv* priv; } ;

/* Variables and functions */
 int tda9950_open (struct tda9950_priv*) ; 
 int /*<<< orphan*/  tda9950_release (struct tda9950_priv*) ; 

__attribute__((used)) static int tda9950_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct tda9950_priv *priv = adap->priv;

	if (!enable) {
		tda9950_release(priv);
		return 0;
	} else {
		return tda9950_open(priv);
	}
}