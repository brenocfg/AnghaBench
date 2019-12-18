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
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPTCTRL_RXE ; 
 int /*<<< orphan*/  ENDPTCTRL_TXE ; 
 scalar_t__ OP_ENDPTCTRL ; 
 int TX ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_ep_disable(struct ci_hdrc *ci, int num, int dir)
{
	hw_write(ci, OP_ENDPTCTRL + num,
		 (dir == TX) ? ENDPTCTRL_TXE : ENDPTCTRL_RXE, 0);
	return 0;
}