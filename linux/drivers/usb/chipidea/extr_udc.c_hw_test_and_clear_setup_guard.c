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
 int /*<<< orphan*/  OP_USBCMD ; 
 int /*<<< orphan*/  USBCMD_SUTW ; 
 int hw_test_and_write (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_test_and_clear_setup_guard(struct ci_hdrc *ci)
{
	return hw_test_and_write(ci, OP_USBCMD, USBCMD_SUTW, 0);
}