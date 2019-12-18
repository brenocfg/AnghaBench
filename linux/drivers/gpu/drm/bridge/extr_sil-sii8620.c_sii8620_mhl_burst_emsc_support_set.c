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
struct mhl_burst_emsc_support {int num_entries; int /*<<< orphan*/ * burst_id; int /*<<< orphan*/  hdr; } ;
typedef  enum mhl_burst_id { ____Placeholder_mhl_burst_id } mhl_burst_id ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_BURST_ID_EMSC_SUPPORT ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  sii8620_mhl_burst_hdr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_mhl_burst_emsc_support_set(struct mhl_burst_emsc_support *d,
	enum mhl_burst_id id)
{
	sii8620_mhl_burst_hdr_set(&d->hdr, MHL_BURST_ID_EMSC_SUPPORT);
	d->num_entries = 1;
	d->burst_id[0] = cpu_to_be16(id);
}