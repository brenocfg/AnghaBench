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
struct cudbg_tid_data {int tid; int* data; } ;
struct cudbg_tcam {int dummy; } ;

/* Variables and functions */
 int LE_ET_HASH_CON ; 
 int LE_ET_TCAM_CON ; 
 int cudbg_get_le_type (int,struct cudbg_tcam) ; 

__attribute__((used)) static int cudbg_is_ipv6_entry(struct cudbg_tid_data *tid_data,
			       struct cudbg_tcam tcam_region)
{
	int ipv6 = 0;
	int le_type;

	le_type = cudbg_get_le_type(tid_data->tid, tcam_region);
	if (tid_data->tid & 1)
		return 0;

	if (le_type == LE_ET_HASH_CON) {
		ipv6 = tid_data->data[16] & 0x8000;
	} else if (le_type == LE_ET_TCAM_CON) {
		ipv6 = tid_data->data[16] & 0x8000;
		if (ipv6)
			ipv6 = tid_data->data[9] == 0x00C00000;
	} else {
		ipv6 = 0;
	}
	return ipv6;
}