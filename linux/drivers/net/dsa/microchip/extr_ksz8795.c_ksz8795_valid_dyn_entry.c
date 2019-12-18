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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int DYNAMIC_MAC_TABLE_MAC_EMPTY ; 
 int DYNAMIC_MAC_TABLE_NOT_READY ; 
 int EAGAIN ; 
 int ENXIO ; 
 int /*<<< orphan*/  REG_IND_DATA_8 ; 
 int /*<<< orphan*/  REG_IND_DATA_CHECK ; 
 int /*<<< orphan*/  ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ksz8795_valid_dyn_entry(struct ksz_device *dev, u8 *data)
{
	int timeout = 100;

	do {
		ksz_read8(dev, REG_IND_DATA_CHECK, data);
		timeout--;
	} while ((*data & DYNAMIC_MAC_TABLE_NOT_READY) && timeout);

	/* Entry is not ready for accessing. */
	if (*data & DYNAMIC_MAC_TABLE_NOT_READY) {
		return -EAGAIN;
	/* Entry is ready for accessing. */
	} else {
		ksz_read8(dev, REG_IND_DATA_8, data);

		/* There is no valid entry in the table. */
		if (*data & DYNAMIC_MAC_TABLE_MAC_EMPTY)
			return -ENXIO;
	}
	return 0;
}