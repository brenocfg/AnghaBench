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
struct ipu_soc {int dummy; } ;
struct ipu_crtc {int /*<<< orphan*/  di; int /*<<< orphan*/  dc; TYPE_1__* dev; } ;
struct ipu_client_platformdata {int /*<<< orphan*/  di; int /*<<< orphan*/  dc; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct ipu_soc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dc_get (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_get (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_put_resources (struct ipu_crtc*) ; 

__attribute__((used)) static int ipu_get_resources(struct ipu_crtc *ipu_crtc,
		struct ipu_client_platformdata *pdata)
{
	struct ipu_soc *ipu = dev_get_drvdata(ipu_crtc->dev->parent);
	int ret;

	ipu_crtc->dc = ipu_dc_get(ipu, pdata->dc);
	if (IS_ERR(ipu_crtc->dc)) {
		ret = PTR_ERR(ipu_crtc->dc);
		goto err_out;
	}

	ipu_crtc->di = ipu_di_get(ipu, pdata->di);
	if (IS_ERR(ipu_crtc->di)) {
		ret = PTR_ERR(ipu_crtc->di);
		goto err_out;
	}

	return 0;
err_out:
	ipu_put_resources(ipu_crtc);

	return ret;
}