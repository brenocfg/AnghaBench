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
struct TYPE_2__ {unsigned int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCLR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CBIT (int /*<<< orphan*/ ,int) ; 
 int EIO ; 
 TYPE_1__* mtd ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int) ; 
 int /*<<< orphan*/ * wbuffer ; 

__attribute__((used)) static int insert_biterror(unsigned byte)
{
	int bit;

	while (byte < mtd->writesize) {
		for (bit = 7; bit >= 0; bit--) {
			if (CBIT(wbuffer[byte], bit)) {
				BCLR(wbuffer[byte], bit);
				pr_info("Inserted biterror @ %u/%u\n", byte, bit);
				return 0;
			}
		}
		byte++;
	}
	pr_err("biterror: Failed to find a '1' bit\n");
	return -EIO;
}