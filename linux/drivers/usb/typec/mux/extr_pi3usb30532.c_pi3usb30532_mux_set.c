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
typedef  int u8 ;
struct typec_mux {int dummy; } ;
struct pi3usb30532 {int conf; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int PI3USB30532_CONF_4LANE_DP ; 
 int PI3USB30532_CONF_OPEN ; 
 int PI3USB30532_CONF_SWAP ; 
 int PI3USB30532_CONF_USB3 ; 
 int PI3USB30532_CONF_USB3_AND_2LANE_DP ; 
#define  TYPEC_DP_STATE_C 132 
#define  TYPEC_DP_STATE_D 131 
#define  TYPEC_DP_STATE_E 130 
#define  TYPEC_STATE_SAFE 129 
#define  TYPEC_STATE_USB 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pi3usb30532_set_conf (struct pi3usb30532*,int) ; 
 struct pi3usb30532* typec_mux_get_drvdata (struct typec_mux*) ; 

__attribute__((used)) static int pi3usb30532_mux_set(struct typec_mux *mux, int state)
{
	struct pi3usb30532 *pi = typec_mux_get_drvdata(mux);
	u8 new_conf;
	int ret;

	mutex_lock(&pi->lock);
	new_conf = pi->conf;

	switch (state) {
	case TYPEC_STATE_SAFE:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_OPEN;
		break;
	case TYPEC_STATE_USB:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_USB3;
		break;
	case TYPEC_DP_STATE_C:
	case TYPEC_DP_STATE_E:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_4LANE_DP;
		break;
	case TYPEC_DP_STATE_D:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_USB3_AND_2LANE_DP;
		break;
	default:
		break;
	}

	ret = pi3usb30532_set_conf(pi, new_conf);
	mutex_unlock(&pi->lock);

	return ret;
}