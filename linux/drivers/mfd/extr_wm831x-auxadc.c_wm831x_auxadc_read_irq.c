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
struct wm831x_auxadc_req {int input; int val; int /*<<< orphan*/  list; int /*<<< orphan*/  done; } ;
struct wm831x {int auxadc_active; int /*<<< orphan*/  auxadc_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  auxadc_pending; } ;
typedef  enum wm831x_auxadc { ____Placeholder_wm831x_auxadc } wm831x_auxadc ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WM831X_AUXADC_CONTROL ; 
 int /*<<< orphan*/  WM831X_AUXADC_SOURCE ; 
 int WM831X_AUX_CVT_ENA ; 
 int WM831X_AUX_ENA ; 
 int WM831X_AUX_RATE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct wm831x_auxadc_req*) ; 
 struct wm831x_auxadc_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm831x_auxadc_read_irq(struct wm831x *wm831x,
				  enum wm831x_auxadc input)
{
	struct wm831x_auxadc_req *req;
	int ret;
	bool ena = false;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	init_completion(&req->done);
	req->input = input;
	req->val = -ETIMEDOUT;

	mutex_lock(&wm831x->auxadc_lock);

	/* Enqueue the request */
	list_add(&req->list, &wm831x->auxadc_pending);

	ena = !wm831x->auxadc_active;

	if (ena) {
		ret = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTROL,
				      WM831X_AUX_ENA, WM831X_AUX_ENA);
		if (ret != 0) {
			dev_err(wm831x->dev, "Failed to enable AUXADC: %d\n",
				ret);
			goto out;
		}
	}

	/* Enable the conversion if not already running */
	if (!(wm831x->auxadc_active & (1 << input))) {
		ret = wm831x_set_bits(wm831x, WM831X_AUXADC_SOURCE,
				      1 << input, 1 << input);
		if (ret != 0) {
			dev_err(wm831x->dev,
				"Failed to set AUXADC source: %d\n", ret);
			goto out;
		}

		wm831x->auxadc_active |= 1 << input;
	}

	/* We convert at the fastest rate possible */
	if (ena) {
		ret = wm831x_set_bits(wm831x, WM831X_AUXADC_CONTROL,
				      WM831X_AUX_CVT_ENA |
				      WM831X_AUX_RATE_MASK,
				      WM831X_AUX_CVT_ENA |
				      WM831X_AUX_RATE_MASK);
		if (ret != 0) {
			dev_err(wm831x->dev, "Failed to start AUXADC: %d\n",
				ret);
			goto out;
		}
	}

	mutex_unlock(&wm831x->auxadc_lock);

	/* Wait for an interrupt */
	wait_for_completion_timeout(&req->done, msecs_to_jiffies(500));

	mutex_lock(&wm831x->auxadc_lock);

	list_del(&req->list);
	ret = req->val;

out:
	mutex_unlock(&wm831x->auxadc_lock);

	kfree(req);

	return ret;
}