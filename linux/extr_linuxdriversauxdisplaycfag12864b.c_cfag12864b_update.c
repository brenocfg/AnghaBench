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
struct work_struct {int dummy; } ;

/* Variables and functions */
 unsigned short CFAG12864B_ADDRESSES ; 
 unsigned short CFAG12864B_CONTROLLERS ; 
 unsigned short CFAG12864B_PAGES ; 
 int /*<<< orphan*/  CFAG12864B_SIZE ; 
 unsigned short CFAG12864B_WIDTH ; 
 unsigned char bit (unsigned short) ; 
 int /*<<< orphan*/  cfag12864b_address (int /*<<< orphan*/ ) ; 
 int* cfag12864b_buffer ; 
 int /*<<< orphan*/  cfag12864b_cache ; 
 int /*<<< orphan*/  cfag12864b_controller (unsigned short) ; 
 int /*<<< orphan*/  cfag12864b_nop () ; 
 int /*<<< orphan*/  cfag12864b_page (unsigned short) ; 
 int /*<<< orphan*/  cfag12864b_queue () ; 
 scalar_t__ cfag12864b_updating ; 
 int /*<<< orphan*/  cfag12864b_writebyte (unsigned char) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfag12864b_update(struct work_struct *work)
{
	unsigned char c;
	unsigned short i, j, k, b;

	if (memcmp(cfag12864b_cache, cfag12864b_buffer, CFAG12864B_SIZE)) {
		for (i = 0; i < CFAG12864B_CONTROLLERS; i++) {
			cfag12864b_controller(i);
			cfag12864b_nop();
			for (j = 0; j < CFAG12864B_PAGES; j++) {
				cfag12864b_page(j);
				cfag12864b_nop();
				cfag12864b_address(0);
				cfag12864b_nop();
				for (k = 0; k < CFAG12864B_ADDRESSES; k++) {
					for (c = 0, b = 0; b < 8; b++)
						if (cfag12864b_buffer
							[i * CFAG12864B_ADDRESSES / 8
							+ k / 8 + (j * 8 + b) *
							CFAG12864B_WIDTH / 8]
							& bit(k % 8))
							c |= bit(b);
					cfag12864b_writebyte(c);
				}
			}
		}

		memcpy(cfag12864b_cache, cfag12864b_buffer, CFAG12864B_SIZE);
	}

	if (cfag12864b_updating)
		cfag12864b_queue();
}