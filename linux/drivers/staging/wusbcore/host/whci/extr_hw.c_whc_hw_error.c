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
struct wusbhc {int dummy; } ;
struct whc {TYPE_1__* umc; struct wusbhc wusbhc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  wusbhc_reset_all (struct wusbhc*) ; 

void whc_hw_error(struct whc *whc, const char *reason)
{
	struct wusbhc *wusbhc = &whc->wusbhc;

	dev_err(&whc->umc->dev, "hardware error: %s\n", reason);
	wusbhc_reset_all(wusbhc);
}