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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_SWRESET_CLEAR ; 
 int /*<<< orphan*/  AX_SWRESET_IPPD ; 
 int /*<<< orphan*/  AX_SWRESET_IPRL ; 
 int asix_sw_reset (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ax88172a_reset_phy(struct usbnet *dev, int embd_phy)
{
	int ret;

	ret = asix_sw_reset(dev, AX_SWRESET_IPPD, 0);
	if (ret < 0)
		goto err;

	msleep(150);
	ret = asix_sw_reset(dev, AX_SWRESET_CLEAR, 0);
	if (ret < 0)
		goto err;

	msleep(150);

	ret = asix_sw_reset(dev, embd_phy ? AX_SWRESET_IPRL : AX_SWRESET_IPPD,
			    0);
	if (ret < 0)
		goto err;

	return 0;

err:
	return ret;
}