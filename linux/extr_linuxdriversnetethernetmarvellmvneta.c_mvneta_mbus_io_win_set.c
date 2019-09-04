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
typedef  int u32 ;
struct mvneta_port {int bm_win_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MVNETA_ACCESS_PROTECT_ENABLE ; 
 int /*<<< orphan*/  MVNETA_BASE_ADDR_ENABLE ; 
 int MVNETA_MAX_DECODE_WIN ; 
 int /*<<< orphan*/  MVNETA_WIN_BASE (int) ; 
 int /*<<< orphan*/  MVNETA_WIN_REMAP (int) ; 
 int /*<<< orphan*/  MVNETA_WIN_SIZE (int) ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mvneta_mbus_io_win_set(struct mvneta_port *pp, u32 base, u32 wsize,
				  u8 target, u8 attr)
{
	u32 win_enable, win_protect;
	int i;

	win_enable = mvreg_read(pp, MVNETA_BASE_ADDR_ENABLE);

	if (pp->bm_win_id < 0) {
		/* Find first not occupied window */
		for (i = 0; i < MVNETA_MAX_DECODE_WIN; i++) {
			if (win_enable & (1 << i)) {
				pp->bm_win_id = i;
				break;
			}
		}
		if (i == MVNETA_MAX_DECODE_WIN)
			return -ENOMEM;
	} else {
		i = pp->bm_win_id;
	}

	mvreg_write(pp, MVNETA_WIN_BASE(i), 0);
	mvreg_write(pp, MVNETA_WIN_SIZE(i), 0);

	if (i < 4)
		mvreg_write(pp, MVNETA_WIN_REMAP(i), 0);

	mvreg_write(pp, MVNETA_WIN_BASE(i), (base & 0xffff0000) |
		    (attr << 8) | target);

	mvreg_write(pp, MVNETA_WIN_SIZE(i), (wsize - 1) & 0xffff0000);

	win_protect = mvreg_read(pp, MVNETA_ACCESS_PROTECT_ENABLE);
	win_protect |= 3 << (2 * i);
	mvreg_write(pp, MVNETA_ACCESS_PROTECT_ENABLE, win_protect);

	win_enable &= ~(1 << i);
	mvreg_write(pp, MVNETA_BASE_ADDR_ENABLE, win_enable);

	return 0;
}