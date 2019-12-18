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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int* data; } ;
struct spinand_device {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int SPINAND_MFR_GIGADEVICE ; 
 int /*<<< orphan*/  gigadevice_spinand_table ; 
 int spinand_match_and_init (struct spinand_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gigadevice_spinand_detect(struct spinand_device *spinand)
{
	u8 *id = spinand->id.data;
	u16 did;
	int ret;

	/*
	 * Earlier GDF5-series devices (A,E) return [0][MID][DID]
	 * Later (F) devices return [MID][DID1][DID2]
	 */

	if (id[0] == SPINAND_MFR_GIGADEVICE)
		did = (id[1] << 8) + id[2];
	else if (id[0] == 0 && id[1] == SPINAND_MFR_GIGADEVICE)
		did = id[2];
	else
		return 0;

	ret = spinand_match_and_init(spinand, gigadevice_spinand_table,
				     ARRAY_SIZE(gigadevice_spinand_table),
				     did);
	if (ret)
		return ret;

	return 1;
}