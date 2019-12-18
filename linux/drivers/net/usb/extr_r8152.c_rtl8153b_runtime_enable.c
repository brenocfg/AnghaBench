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
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8153_queue_wake (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u2p3en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_u1u2en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_ups_en (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_runtime_suspend_enable (struct r8152*,int) ; 

__attribute__((used)) static void rtl8153b_runtime_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		r8153_queue_wake(tp, true);
		r8153b_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runtime_suspend_enable(tp, true);
		r8153b_ups_en(tp, true);
	} else {
		r8153b_ups_en(tp, false);
		r8153_queue_wake(tp, false);
		rtl_runtime_suspend_enable(tp, false);
		r8153_u2p3en(tp, true);
		r8153b_u1u2en(tp, true);
	}
}