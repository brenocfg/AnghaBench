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
struct coh901318_lli {int control; struct coh901318_lli* virt_link_addr; } ;

/* Variables and functions */
 int COH901318_CX_CTRL_TC_VALUE_MASK ; 

__attribute__((used)) static inline u32 coh901318_get_bytes_in_lli(struct coh901318_lli *in_lli)
{
	struct coh901318_lli *lli = in_lli;
	u32 bytes = 0;

	while (lli) {
		bytes += lli->control & COH901318_CX_CTRL_TC_VALUE_MASK;
		lli = lli->virt_link_addr;
	}
	return bytes;
}