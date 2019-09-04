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
struct saa7134_dev {int dummy; } ;
typedef  enum tda18271_mode { ____Placeholder_tda18271_mode } tda18271_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  TDA18271_ANALOG 129 
#define  TDA18271_DIGITAL 128 
 int /*<<< orphan*/  saa7134_set_gpio (struct saa7134_dev*,int,int) ; 

__attribute__((used)) static inline int saa7134_tda18271_hvr11x0_toggle_agc(struct saa7134_dev *dev,
						      enum tda18271_mode mode)
{
	/* toggle AGC switch through GPIO 26 */
	switch (mode) {
	case TDA18271_ANALOG:
		saa7134_set_gpio(dev, 26, 0);
		break;
	case TDA18271_DIGITAL:
		saa7134_set_gpio(dev, 26, 1);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}