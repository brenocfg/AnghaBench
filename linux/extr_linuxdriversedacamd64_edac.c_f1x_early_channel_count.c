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
typedef  int /*<<< orphan*/  u32 ;
struct amd64_pvt {int fam; int dclr0; int /*<<< orphan*/  dbam0; int /*<<< orphan*/  dbam1; } ;

/* Variables and functions */
 scalar_t__ DBAM_DIMM (int,int /*<<< orphan*/ ) ; 
 int WIDTH_128 ; 
 int /*<<< orphan*/  amd64_info (char*,int) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int f1x_early_channel_count(struct amd64_pvt *pvt)
{
	int i, j, channels = 0;

	/* On F10h, if we are in 128 bit mode, then we are using 2 channels */
	if (pvt->fam == 0x10 && (pvt->dclr0 & WIDTH_128))
		return 2;

	/*
	 * Need to check if in unganged mode: In such, there are 2 channels,
	 * but they are not in 128 bit mode and thus the above 'dclr0' status
	 * bit will be OFF.
	 *
	 * Need to check DCT0[0] and DCT1[0] to see if only one of them has
	 * their CSEnable bit on. If so, then SINGLE DIMM case.
	 */
	edac_dbg(0, "Data width is not 128 bits - need more decoding\n");

	/*
	 * Check DRAM Bank Address Mapping values for each DIMM to see if there
	 * is more than just one DIMM present in unganged mode. Need to check
	 * both controllers since DIMMs can be placed in either one.
	 */
	for (i = 0; i < 2; i++) {
		u32 dbam = (i ? pvt->dbam1 : pvt->dbam0);

		for (j = 0; j < 4; j++) {
			if (DBAM_DIMM(j, dbam) > 0) {
				channels++;
				break;
			}
		}
	}

	if (channels > 2)
		channels = 2;

	amd64_info("MCT channel count: %d\n", channels);

	return channels;
}