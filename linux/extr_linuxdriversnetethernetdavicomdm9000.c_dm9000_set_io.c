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
struct board_info {int /*<<< orphan*/  inblk; int /*<<< orphan*/  outblk; int /*<<< orphan*/  dumpblk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dm9000_dumpblk_16bit ; 
 int /*<<< orphan*/  dm9000_dumpblk_32bit ; 
 int /*<<< orphan*/  dm9000_dumpblk_8bit ; 
 int /*<<< orphan*/  dm9000_inblk_16bit ; 
 int /*<<< orphan*/  dm9000_inblk_32bit ; 
 int /*<<< orphan*/  dm9000_inblk_8bit ; 
 int /*<<< orphan*/  dm9000_outblk_16bit ; 
 int /*<<< orphan*/  dm9000_outblk_32bit ; 
 int /*<<< orphan*/  dm9000_outblk_8bit ; 

__attribute__((used)) static void dm9000_set_io(struct board_info *db, int byte_width)
{
	/* use the size of the data resource to work out what IO
	 * routines we want to use
	 */

	switch (byte_width) {
	case 1:
		db->dumpblk = dm9000_dumpblk_8bit;
		db->outblk  = dm9000_outblk_8bit;
		db->inblk   = dm9000_inblk_8bit;
		break;


	case 3:
		dev_dbg(db->dev, ": 3 byte IO, falling back to 16bit\n");
	case 2:
		db->dumpblk = dm9000_dumpblk_16bit;
		db->outblk  = dm9000_outblk_16bit;
		db->inblk   = dm9000_inblk_16bit;
		break;

	case 4:
	default:
		db->dumpblk = dm9000_dumpblk_32bit;
		db->outblk  = dm9000_outblk_32bit;
		db->inblk   = dm9000_inblk_32bit;
		break;
	}
}