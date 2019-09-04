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
typedef  int /*<<< orphan*/  uint16_t ;
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  const* get_filter_2tap_16p () ; 
 int /*<<< orphan*/  const* get_filter_3tap_16p (struct fixed31_32) ; 
 int /*<<< orphan*/  const* get_filter_4tap_16p (struct fixed31_32) ; 

__attribute__((used)) static const uint16_t *get_filter_coeffs_16p(int taps, struct fixed31_32 ratio)
{
	if (taps == 4)
		return get_filter_4tap_16p(ratio);
	else if (taps == 3)
		return get_filter_3tap_16p(ratio);
	else if (taps == 2)
		return get_filter_2tap_16p();
	else if (taps == 1)
		return NULL;
	else {
		/* should never happen, bug */
		BREAK_TO_DEBUGGER();
		return NULL;
	}
}