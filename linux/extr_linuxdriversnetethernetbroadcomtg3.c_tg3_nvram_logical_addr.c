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
typedef  int u32 ;
struct tg3 {scalar_t__ nvram_jedecnum; int nvram_pagesize; } ;

/* Variables and functions */
 int ATMEL_AT45DB0X1B_PAGE_POS ; 
 int /*<<< orphan*/  FLASH ; 
 scalar_t__ JEDEC_ATMEL ; 
 int /*<<< orphan*/  NO_NVRAM_ADDR_TRANS ; 
 int /*<<< orphan*/  NVRAM ; 
 int /*<<< orphan*/  NVRAM_BUFFERED ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 tg3_nvram_logical_addr(struct tg3 *tp, u32 addr)
{
	if (tg3_flag(tp, NVRAM) &&
	    tg3_flag(tp, NVRAM_BUFFERED) &&
	    tg3_flag(tp, FLASH) &&
	    !tg3_flag(tp, NO_NVRAM_ADDR_TRANS) &&
	    (tp->nvram_jedecnum == JEDEC_ATMEL))

		addr = ((addr >> ATMEL_AT45DB0X1B_PAGE_POS) *
			tp->nvram_pagesize) +
		       (addr & ((1 << ATMEL_AT45DB0X1B_PAGE_POS) - 1));

	return addr;
}