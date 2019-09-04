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
struct hfi1_devdata {size_t hfi1_id; struct hfi1_asic_data* asic_data; } ;
struct hfi1_asic_data {int /*<<< orphan*/ ** dds; } ;

/* Variables and functions */

__attribute__((used)) static struct hfi1_asic_data *release_asic_data(struct hfi1_devdata *dd)
{
	struct hfi1_asic_data *ad;
	int other;

	if (!dd->asic_data)
		return NULL;
	dd->asic_data->dds[dd->hfi1_id] = NULL;
	other = dd->hfi1_id ? 0 : 1;
	ad = dd->asic_data;
	dd->asic_data = NULL;
	/* return NULL if the other dd still has a link */
	return ad->dds[other] ? NULL : ad;
}