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
struct pinctrl_dev {int dummy; } ;
struct dc_pinmap {char** pin_names; } ;

/* Variables and functions */
 unsigned int PINS_COUNT ; 
 struct dc_pinmap* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int dc_get_groups(struct pinctrl_dev *pctldev, unsigned selector,
			 const char * const **groups,
			 unsigned * const num_groups)
{
	struct dc_pinmap *pmap = pinctrl_dev_get_drvdata(pctldev);

	*groups = pmap->pin_names;
	*num_groups = PINS_COUNT;

	return 0;
}