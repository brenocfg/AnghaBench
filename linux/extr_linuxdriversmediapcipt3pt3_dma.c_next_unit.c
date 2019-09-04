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
typedef  int /*<<< orphan*/  u8 ;
struct pt3_adapter {int num_bufs; TYPE_1__* buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DATA_BUF_SZ ; 
 scalar_t__ PT3_ACCESS_UNIT ; 

__attribute__((used)) static u8 *next_unit(struct pt3_adapter *adap, int *idx, int *ofs)
{
	*ofs += PT3_ACCESS_UNIT;
	if (*ofs >= DATA_BUF_SZ) {
		*ofs -= DATA_BUF_SZ;
		(*idx)++;
		if (*idx == adap->num_bufs)
			*idx = 0;
	}
	return &adap->buffer[*idx].data[*ofs];
}