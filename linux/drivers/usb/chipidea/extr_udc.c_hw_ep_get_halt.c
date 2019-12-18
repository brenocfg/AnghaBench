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
typedef  int /*<<< orphan*/  u32 ;
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPTCTRL_RXS ; 
 int /*<<< orphan*/  ENDPTCTRL_TXS ; 
 scalar_t__ OP_ENDPTCTRL ; 
 int TX ; 
 scalar_t__ hw_read (struct ci_hdrc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_ep_get_halt(struct ci_hdrc *ci, int num, int dir)
{
	u32 mask = (dir == TX) ? ENDPTCTRL_TXS : ENDPTCTRL_RXS;

	return hw_read(ci, OP_ENDPTCTRL + num, mask) ? 1 : 0;
}