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
typedef  int /*<<< orphan*/  u8 ;
struct typec_switch {int dummy; } ;
struct pi3usb30532 {int /*<<< orphan*/  lock; int /*<<< orphan*/  conf; } ;
typedef  enum typec_orientation { ____Placeholder_typec_orientation } typec_orientation ;

/* Variables and functions */
 int /*<<< orphan*/  PI3USB30532_CONF_OPEN ; 
 int /*<<< orphan*/  PI3USB30532_CONF_SWAP ; 
#define  TYPEC_ORIENTATION_NONE 130 
#define  TYPEC_ORIENTATION_NORMAL 129 
#define  TYPEC_ORIENTATION_REVERSE 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pi3usb30532_set_conf (struct pi3usb30532*,int /*<<< orphan*/ ) ; 
 struct pi3usb30532* typec_switch_get_drvdata (struct typec_switch*) ; 

__attribute__((used)) static int pi3usb30532_sw_set(struct typec_switch *sw,
			      enum typec_orientation orientation)
{
	struct pi3usb30532 *pi = typec_switch_get_drvdata(sw);
	u8 new_conf;
	int ret;

	mutex_lock(&pi->lock);
	new_conf = pi->conf;

	switch (orientation) {
	case TYPEC_ORIENTATION_NONE:
		new_conf = PI3USB30532_CONF_OPEN;
		break;
	case TYPEC_ORIENTATION_NORMAL:
		new_conf &= ~PI3USB30532_CONF_SWAP;
		break;
	case TYPEC_ORIENTATION_REVERSE:
		new_conf |= PI3USB30532_CONF_SWAP;
		break;
	}

	ret = pi3usb30532_set_conf(pi, new_conf);
	mutex_unlock(&pi->lock);

	return ret;
}