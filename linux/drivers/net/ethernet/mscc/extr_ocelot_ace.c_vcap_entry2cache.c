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
typedef  size_t u32 ;
struct vcap_data {int /*<<< orphan*/  tg; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * entry; } ;
struct ocelot {int dummy; } ;
struct TYPE_2__ {size_t entry_words; } ;

/* Variables and functions */
 int /*<<< orphan*/  S2_CACHE_ENTRY_DAT ; 
 int /*<<< orphan*/  S2_CACHE_MASK_DAT ; 
 int /*<<< orphan*/  S2_CACHE_TG_DAT ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_rix (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ vcap_is2 ; 

__attribute__((used)) static void vcap_entry2cache(struct ocelot *oc, struct vcap_data *data)
{
	u32 i;

	for (i = 0; i < vcap_is2.entry_words; i++) {
		ocelot_write_rix(oc, data->entry[i], S2_CACHE_ENTRY_DAT, i);
		ocelot_write_rix(oc, ~data->mask[i], S2_CACHE_MASK_DAT, i);
	}
	ocelot_write(oc, data->tg, S2_CACHE_TG_DAT);
}