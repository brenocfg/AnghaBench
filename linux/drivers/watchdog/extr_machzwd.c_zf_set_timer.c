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

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_1 ; 
 int /*<<< orphan*/  COUNTER_2 ; 
#define  WD1 129 
#define  WD2 128 
 int /*<<< orphan*/  zf_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zf_writew (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static inline void zf_set_timer(unsigned short new, unsigned char n)
{
	switch (n) {
	case WD1:
		zf_writew(COUNTER_1, new);
		/* fall through */
	case WD2:
		zf_writeb(COUNTER_2, new > 0xff ? 0xff : new);
	default:
		return;
	}
}