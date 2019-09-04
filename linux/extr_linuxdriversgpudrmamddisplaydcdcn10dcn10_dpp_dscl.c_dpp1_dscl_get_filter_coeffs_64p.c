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
 int /*<<< orphan*/  const* get_filter_2tap_64p () ; 
 int /*<<< orphan*/  const* get_filter_3tap_64p (struct fixed31_32) ; 
 int /*<<< orphan*/  const* get_filter_4tap_64p (struct fixed31_32) ; 
 int /*<<< orphan*/  const* get_filter_5tap_64p (struct fixed31_32) ; 
 int /*<<< orphan*/  const* get_filter_6tap_64p (struct fixed31_32) ; 
 int /*<<< orphan*/  const* get_filter_7tap_64p (struct fixed31_32) ; 
 int /*<<< orphan*/  const* get_filter_8tap_64p (struct fixed31_32) ; 

__attribute__((used)) static const uint16_t *dpp1_dscl_get_filter_coeffs_64p(int taps, struct fixed31_32 ratio)
{
	if (taps == 8)
		return get_filter_8tap_64p(ratio);
	else if (taps == 7)
		return get_filter_7tap_64p(ratio);
	else if (taps == 6)
		return get_filter_6tap_64p(ratio);
	else if (taps == 5)
		return get_filter_5tap_64p(ratio);
	else if (taps == 4)
		return get_filter_4tap_64p(ratio);
	else if (taps == 3)
		return get_filter_3tap_64p(ratio);
	else if (taps == 2)
		return get_filter_2tap_64p();
	else if (taps == 1)
		return NULL;
	else {
		/* should never happen, bug */
		BREAK_TO_DEBUGGER();
		return NULL;
	}
}