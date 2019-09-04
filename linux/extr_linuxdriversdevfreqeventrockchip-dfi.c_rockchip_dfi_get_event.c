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
struct rockchip_dfi {TYPE_1__* ch_usage; } ;
struct devfreq_event_dev {int dummy; } ;
struct devfreq_event_data {int /*<<< orphan*/  total_count; int /*<<< orphan*/  load_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  total; int /*<<< orphan*/  access; } ;

/* Variables and functions */
 struct rockchip_dfi* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int rockchip_dfi_get_busier_ch (struct devfreq_event_dev*) ; 

__attribute__((used)) static int rockchip_dfi_get_event(struct devfreq_event_dev *edev,
				  struct devfreq_event_data *edata)
{
	struct rockchip_dfi *info = devfreq_event_get_drvdata(edev);
	int busier_ch;

	busier_ch = rockchip_dfi_get_busier_ch(edev);

	edata->load_count = info->ch_usage[busier_ch].access;
	edata->total_count = info->ch_usage[busier_ch].total;

	return 0;
}