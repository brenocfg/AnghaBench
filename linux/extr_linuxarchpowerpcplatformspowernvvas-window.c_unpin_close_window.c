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
typedef  int /*<<< orphan*/  u64 ;
struct vas_window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAS_WINCTL_OPEN ; 
 int /*<<< orphan*/  VAS_WINCTL_PIN ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINCTL ; 
 int /*<<< orphan*/  read_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unpin_close_window(struct vas_window *window)
{
	u64 val;

	val = read_hvwc_reg(window, VREG(WINCTL));
	val = SET_FIELD(VAS_WINCTL_PIN, val, 0);
	val = SET_FIELD(VAS_WINCTL_OPEN, val, 0);
	write_hvwc_reg(window, VREG(WINCTL), val);
}