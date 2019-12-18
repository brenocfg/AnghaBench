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
typedef  int u32 ;
struct usb_hcd {int /*<<< orphan*/  regs; } ;
struct isp1760_hcd {int periodic_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_FRINDEX ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int reg_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isp1760_get_frame(struct usb_hcd *hcd)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 fr;

	fr = reg_read32(hcd->regs, HC_FRINDEX);
	return (fr >> 3) % priv->periodic_size;
}