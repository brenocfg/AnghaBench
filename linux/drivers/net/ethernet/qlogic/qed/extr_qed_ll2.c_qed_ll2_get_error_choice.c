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
typedef  enum qed_ll2_error_handle { ____Placeholder_qed_ll2_error_handle } qed_ll2_error_handle ;
typedef  enum core_error_handle { ____Placeholder_core_error_handle } core_error_handle ;

/* Variables and functions */
 int LL2_ASSERT ; 
 int LL2_DO_NOTHING ; 
 int LL2_DROP_PACKET ; 
#define  QED_LL2_ASSERT 130 
#define  QED_LL2_DO_NOTHING 129 
#define  QED_LL2_DROP_PACKET 128 

__attribute__((used)) static enum core_error_handle
qed_ll2_get_error_choice(enum qed_ll2_error_handle err)
{
	switch (err) {
	case QED_LL2_DROP_PACKET:
		return LL2_DROP_PACKET;
	case QED_LL2_DO_NOTHING:
		return LL2_DO_NOTHING;
	case QED_LL2_ASSERT:
		return LL2_ASSERT;
	default:
		return LL2_DO_NOTHING;
	}
}