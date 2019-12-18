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
struct TYPE_2__ {int /*<<< orphan*/  ecc_chunk_size; } ;
struct gpmi_nand_data {TYPE_1__ bch_geometry; scalar_t__ bch; } ;

/* Variables and functions */
 int ALIGN_DOWN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpmi_raw_len_to_len(struct gpmi_nand_data *this, int raw_len)
{
	/*
	 * raw_len is the length to read/write including bch data which
	 * we are passed in exec_op. Calculate the data length from it.
	 */
	if (this->bch)
		return ALIGN_DOWN(raw_len, this->bch_geometry.ecc_chunk_size);
	else
		return raw_len;
}