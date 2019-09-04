#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hw_supported; } ;
struct ddc {TYPE_1__ hw_info; } ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int GPIO_DDC_LINE_COUNT ; 
 int GPIO_DDC_LINE_UNKNOWN ; 
 int dal_ddc_get_line (struct ddc*) ; 

__attribute__((used)) static bool get_hw_supported_ddc_line(
	struct ddc *ddc,
	enum gpio_ddc_line *line)
{
	enum gpio_ddc_line line_found;

	*line = GPIO_DDC_LINE_UNKNOWN;

	if (!ddc) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!ddc->hw_info.hw_supported)
		return false;

	line_found = dal_ddc_get_line(ddc);

	if (line_found >= GPIO_DDC_LINE_COUNT)
		return false;

	*line = line_found;

	return true;
}