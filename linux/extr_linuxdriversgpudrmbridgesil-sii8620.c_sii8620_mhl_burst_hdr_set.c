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
struct mhl3_burst_header {int total_entries; int sequence_index; int /*<<< orphan*/  id; } ;
typedef  enum mhl_burst_id { ____Placeholder_mhl_burst_id } mhl_burst_id ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

__attribute__((used)) static void sii8620_mhl_burst_hdr_set(struct mhl3_burst_header *h,
	enum mhl_burst_id id)
{
	h->id = cpu_to_be16(id);
	h->total_entries = 1;
	h->sequence_index = 1;
}