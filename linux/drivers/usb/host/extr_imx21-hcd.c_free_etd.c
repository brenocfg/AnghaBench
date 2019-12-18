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
struct imx21 {TYPE_1__* etd; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ alloc; } ;

/* Variables and functions */
 int USB_NUM_ETD ; 
 int /*<<< orphan*/  debug_etd_freed (struct imx21*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_etd (struct imx21*,int) ; 

__attribute__((used)) static void free_etd(struct imx21 *imx21, int num)
{
	if (num < 0)
		return;

	if (num >= USB_NUM_ETD) {
		dev_err(imx21->dev, "BAD etd=%d!\n", num);
		return;
	}
	if (imx21->etd[num].alloc == 0) {
		dev_err(imx21->dev, "ETD %d already free!\n", num);
		return;
	}

	debug_etd_freed(imx21);
	reset_etd(imx21, num);
	memset(&imx21->etd[num], 0, sizeof(imx21->etd[0]));
}