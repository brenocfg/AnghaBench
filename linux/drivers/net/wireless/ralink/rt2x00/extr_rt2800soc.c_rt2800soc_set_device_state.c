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
struct rt2x00_dev {int dummy; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  STATE_AWAKE 135 
#define  STATE_DEEP_SLEEP 134 
#define  STATE_RADIO_IRQ_OFF 133 
#define  STATE_RADIO_IRQ_ON 132 
#define  STATE_RADIO_OFF 131 
#define  STATE_RADIO_ON 130 
#define  STATE_SLEEP 129 
#define  STATE_STANDBY 128 
 int rt2800mmio_enable_radio (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800mmio_toggle_irq (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800soc_disable_radio (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rt2800soc_set_device_state(struct rt2x00_dev *rt2x00dev,
				      enum dev_state state)
{
	int retval = 0;

	switch (state) {
	case STATE_RADIO_ON:
		retval = rt2800mmio_enable_radio(rt2x00dev);
		break;

	case STATE_RADIO_OFF:
		rt2800soc_disable_radio(rt2x00dev);
		break;

	case STATE_RADIO_IRQ_ON:
	case STATE_RADIO_IRQ_OFF:
		rt2800mmio_toggle_irq(rt2x00dev, state);
		break;

	case STATE_DEEP_SLEEP:
	case STATE_SLEEP:
	case STATE_STANDBY:
	case STATE_AWAKE:
		/* These states are not supported, but don't report an error */
		retval = 0;
		break;

	default:
		retval = -ENOTSUPP;
		break;
	}

	if (unlikely(retval))
		rt2x00_err(rt2x00dev, "Device failed to enter state %d (%d)\n",
			   state, retval);

	return retval;
}