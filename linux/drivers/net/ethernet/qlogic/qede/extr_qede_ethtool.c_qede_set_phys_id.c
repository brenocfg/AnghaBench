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
typedef  int /*<<< orphan*/  u8 ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;
struct TYPE_4__ {TYPE_1__* common; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_led ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  QED_LED_MODE_OFF ; 
 int /*<<< orphan*/  QED_LED_MODE_ON ; 
 int /*<<< orphan*/  QED_LED_MODE_RESTORE ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_set_phys_id(struct net_device *dev,
			    enum ethtool_phys_id_state state)
{
	struct qede_dev *edev = netdev_priv(dev);
	u8 led_state = 0;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		return 1;	/* cycle on/off once per second */

	case ETHTOOL_ID_ON:
		led_state = QED_LED_MODE_ON;
		break;

	case ETHTOOL_ID_OFF:
		led_state = QED_LED_MODE_OFF;
		break;

	case ETHTOOL_ID_INACTIVE:
		led_state = QED_LED_MODE_RESTORE;
		break;
	}

	edev->ops->common->set_led(edev->cdev, led_state);

	return 0;
}