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
struct tg3 {int /*<<< orphan*/  nvram_pagesize; int /*<<< orphan*/  nvram_jedecnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_AT24C512_CHIP_SIZE ; 
 int /*<<< orphan*/  JEDEC_ATMEL ; 
 int /*<<< orphan*/  NVRAM_BUFFERED ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_get_5906_nvram_info(struct tg3 *tp)
{
	tp->nvram_jedecnum = JEDEC_ATMEL;
	tg3_flag_set(tp, NVRAM_BUFFERED);
	tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;
}