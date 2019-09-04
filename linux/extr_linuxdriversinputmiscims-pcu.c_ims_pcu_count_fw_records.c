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
struct ihex_binrec {int dummy; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 

__attribute__((used)) static unsigned int ims_pcu_count_fw_records(const struct firmware *fw)
{
	const struct ihex_binrec *rec = (const struct ihex_binrec *)fw->data;
	unsigned int count = 0;

	while (rec) {
		count++;
		rec = ihex_next_binrec(rec);
	}

	return count;
}