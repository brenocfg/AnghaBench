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
struct imx6ul_tsc {int dummy; } ;

/* Variables and functions */
 int imx6ul_adc_init (struct imx6ul_tsc*) ; 
 int /*<<< orphan*/  imx6ul_tsc_channel_config (struct imx6ul_tsc*) ; 
 int /*<<< orphan*/  imx6ul_tsc_set (struct imx6ul_tsc*) ; 

__attribute__((used)) static int imx6ul_tsc_init(struct imx6ul_tsc *tsc)
{
	int err;

	err = imx6ul_adc_init(tsc);
	if (err)
		return err;
	imx6ul_tsc_channel_config(tsc);
	imx6ul_tsc_set(tsc);

	return 0;
}