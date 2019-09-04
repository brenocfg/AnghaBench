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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct isc_ctrls {int* hist_count; size_t hist_id; int* hist_entry; } ;
struct isc_device {struct isc_ctrls ctrls; struct regmap* regmap; } ;

/* Variables and functions */
 int HIST_ENTRIES ; 
 int /*<<< orphan*/  ISC_HIS_ENTRY ; 
 int /*<<< orphan*/  regmap_bulk_read (struct regmap*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void isc_hist_count(struct isc_device *isc)
{
	struct regmap *regmap = isc->regmap;
	struct isc_ctrls *ctrls = &isc->ctrls;
	u32 *hist_count = &ctrls->hist_count[ctrls->hist_id];
	u32 *hist_entry = &ctrls->hist_entry[0];
	u32 i;

	regmap_bulk_read(regmap, ISC_HIS_ENTRY, hist_entry, HIST_ENTRIES);

	*hist_count = 0;
	for (i = 0; i < HIST_ENTRIES; i++)
		*hist_count += i * (*hist_entry++);
}