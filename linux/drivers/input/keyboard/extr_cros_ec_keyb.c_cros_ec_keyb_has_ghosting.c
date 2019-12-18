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
typedef  int uint8_t ;
struct device {int dummy; } ;
struct cros_ec_keyb {int* valid_keys; int cols; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int,int) ; 
 int hweight8 (int) ; 

__attribute__((used)) static bool cros_ec_keyb_has_ghosting(struct cros_ec_keyb *ckdev, uint8_t *buf)
{
	int col1, col2, buf1, buf2;
	struct device *dev = ckdev->dev;
	uint8_t *valid_keys = ckdev->valid_keys;

	/*
	 * Ghosting happens if for any pressed key X there are other keys
	 * pressed both in the same row and column of X as, for instance,
	 * in the following diagram:
	 *
	 * . . Y . g .
	 * . . . . . .
	 * . . . . . .
	 * . . X . Z .
	 *
	 * In this case only X, Y, and Z are pressed, but g appears to be
	 * pressed too (see Wikipedia).
	 */
	for (col1 = 0; col1 < ckdev->cols; col1++) {
		buf1 = buf[col1] & valid_keys[col1];
		for (col2 = col1 + 1; col2 < ckdev->cols; col2++) {
			buf2 = buf[col2] & valid_keys[col2];
			if (hweight8(buf1 & buf2) > 1) {
				dev_dbg(dev, "ghost found at: B[%02d]:0x%02x & B[%02d]:0x%02x",
					col1, buf1, col2, buf2);
				return true;
			}
		}
	}

	return false;
}