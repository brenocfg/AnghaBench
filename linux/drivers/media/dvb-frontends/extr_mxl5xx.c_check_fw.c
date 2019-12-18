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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct mxl {int /*<<< orphan*/  i2cdev; } ;
struct MBIN_FILE_HEADER_T {int* image_size24; char id; char fmt_version; scalar_t__ image_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_fw(struct mxl *state, u8 *mbin, u32 mbin_len)
{
	struct MBIN_FILE_HEADER_T *fh = (struct MBIN_FILE_HEADER_T *) mbin;
	u32 flen = (fh->image_size24[0] << 16) |
		(fh->image_size24[1] <<  8) | fh->image_size24[2];
	u8 *fw, cs = 0;
	u32 i;

	if (fh->id != 'M' || fh->fmt_version != '1' || flen > 0x3FFF0) {
		dev_info(state->i2cdev, "Invalid FW Header\n");
		return -1;
	}
	fw = mbin + sizeof(struct MBIN_FILE_HEADER_T);
	for (i = 0; i < flen; i += 1)
		cs += fw[i];
	if (cs != fh->image_checksum) {
		dev_info(state->i2cdev, "Invalid FW Checksum\n");
		return -1;
	}
	return 0;
}