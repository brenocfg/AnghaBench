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
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int ENDPTCTRL_RXE ; 
 int ENDPTCTRL_RXR ; 
 int ENDPTCTRL_RXS ; 
 int ENDPTCTRL_RXT ; 
 int ENDPTCTRL_TXE ; 
 int ENDPTCTRL_TXR ; 
 int ENDPTCTRL_TXS ; 
 int ENDPTCTRL_TXT ; 
 scalar_t__ OP_ENDPTCTRL ; 
 int TX ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,scalar_t__,int,int) ; 

__attribute__((used)) static int hw_ep_enable(struct ci_hdrc *ci, int num, int dir, int type)
{
	u32 mask, data;

	if (dir == TX) {
		mask  = ENDPTCTRL_TXT;  /* type    */
		data  = type << __ffs(mask);

		mask |= ENDPTCTRL_TXS;  /* unstall */
		mask |= ENDPTCTRL_TXR;  /* reset data toggle */
		data |= ENDPTCTRL_TXR;
		mask |= ENDPTCTRL_TXE;  /* enable  */
		data |= ENDPTCTRL_TXE;
	} else {
		mask  = ENDPTCTRL_RXT;  /* type    */
		data  = type << __ffs(mask);

		mask |= ENDPTCTRL_RXS;  /* unstall */
		mask |= ENDPTCTRL_RXR;  /* reset data toggle */
		data |= ENDPTCTRL_RXR;
		mask |= ENDPTCTRL_RXE;  /* enable  */
		data |= ENDPTCTRL_RXE;
	}
	hw_write(ci, OP_ENDPTCTRL + num, mask, data);
	return 0;
}