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
struct fpgaimage {int /*<<< orphan*/ * fpgadata; int /*<<< orphan*/  lendata; int /*<<< orphan*/  time; int /*<<< orphan*/  date; int /*<<< orphan*/  part; int /*<<< orphan*/  filename; TYPE_1__* fw_entry; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_STR ; 
 int readinfo_bitstream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int readlength_bitstream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int readmagic_bitstream (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int gs_read_bitstream(struct fpgaimage *fimage)
{
	u8 *bitdata;
	int offset;
	int err;

	offset = 0;
	bitdata = (u8 *)fimage->fw_entry->data;

	err = readmagic_bitstream(bitdata, &offset);
	if (err)
		return err;

	err = readinfo_bitstream(bitdata, fimage->filename, MAX_STR, &offset);
	if (err)
		return err;
	err = readinfo_bitstream(bitdata, fimage->part, MAX_STR, &offset);
	if (err)
		return err;
	err = readinfo_bitstream(bitdata, fimage->date, MAX_STR, &offset);
	if (err)
		return err;
	err = readinfo_bitstream(bitdata, fimage->time, MAX_STR, &offset);
	if (err)
		return err;

	err = readlength_bitstream(bitdata, &fimage->lendata, &offset);
	if (err)
		return err;

	fimage->fpgadata = bitdata + offset;

	return 0;
}