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
struct clk_si544 {int speed_grade; } ;

/* Variables and functions */
 unsigned long SI544_MIN_FREQ ; 
#define  si544a 130 
#define  si544b 129 
#define  si544c 128 

__attribute__((used)) static bool is_valid_frequency(const struct clk_si544 *data,
	unsigned long frequency)
{
	unsigned long max_freq = 0;

	if (frequency < SI544_MIN_FREQ)
		return false;

	switch (data->speed_grade) {
	case si544a:
		max_freq = 1500000000;
		break;
	case si544b:
		max_freq = 800000000;
		break;
	case si544c:
		max_freq = 350000000;
		break;
	}

	return frequency <= max_freq;
}