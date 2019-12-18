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
typedef  int u8 ;
typedef  int u32 ;
struct altera_jtag {int ir_pre; int* ir_pre_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ alt_malloc (int) ; 
 int /*<<< orphan*/  kfree (int*) ; 

int altera_set_ir_pre(struct altera_jtag *js, u32 count, u32 start_index,
							u8 *preamble_data)
{
	int status = 0;
	u32 i;
	u32 j;

	if (count > js->ir_pre) {
		kfree(js->ir_pre_data);
		js->ir_pre_data = (u8 *)alt_malloc((count + 7) >> 3);
		if (js->ir_pre_data == NULL)
			status = -ENOMEM;
		else
			js->ir_pre = count;

	} else
		js->ir_pre = count;

	if (status == 0) {
		for (i = 0; i < count; ++i) {
			j = i + start_index;
			if (preamble_data == NULL)
				js->ir_pre_data[i >> 3] |= (1 << (i & 7));
			else {
				if (preamble_data[j >> 3] & (1 << (j & 7)))
					js->ir_pre_data[i >> 3] |=
							(1 << (i & 7));
				else
					js->ir_pre_data[i >> 3] &=
							~(u32)(1 << (i & 7));

			}
		}
	}

	return status;
}