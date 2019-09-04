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
struct wm97xx_data {int /*<<< orphan*/  p; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wm97xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PRESSURE ; 
 int RC_VALID ; 
 int WM97XX_ADCSEL_PRES ; 
 int WM97XX_ADCSEL_X ; 
 int WM97XX_ADCSEL_Y ; 
 int WM97XX_PEN_DOWN ; 
 scalar_t__ coord ; 
 scalar_t__ pil ; 
 int wm9713_poll_coord (struct wm97xx*,struct wm97xx_data*) ; 
 int wm9713_poll_sample (struct wm97xx*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wm9713_poll_touch(struct wm97xx *wm, struct wm97xx_data *data)
{
	int rc;

	if (coord) {
		rc = wm9713_poll_coord(wm, data);
		if (rc != RC_VALID)
			return rc;
	} else {
		rc = wm9713_poll_sample(wm, WM97XX_ADCSEL_X | WM97XX_PEN_DOWN, &data->x);
		if (rc != RC_VALID)
			return rc;
		rc = wm9713_poll_sample(wm, WM97XX_ADCSEL_Y | WM97XX_PEN_DOWN, &data->y);
		if (rc != RC_VALID)
			return rc;
		if (pil) {
			rc = wm9713_poll_sample(wm, WM97XX_ADCSEL_PRES | WM97XX_PEN_DOWN,
						&data->p);
			if (rc != RC_VALID)
				return rc;
		} else
			data->p = DEFAULT_PRESSURE;
	}
	return RC_VALID;
}