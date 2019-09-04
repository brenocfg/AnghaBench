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
struct tg3 {int nvram_pagesize; } ;

/* Variables and functions */
#define  FLASH_5752PAGE_SIZE_1K 134 
#define  FLASH_5752PAGE_SIZE_256 133 
#define  FLASH_5752PAGE_SIZE_264 132 
#define  FLASH_5752PAGE_SIZE_2K 131 
#define  FLASH_5752PAGE_SIZE_4K 130 
#define  FLASH_5752PAGE_SIZE_512 129 
#define  FLASH_5752PAGE_SIZE_528 128 
 int NVRAM_CFG1_5752PAGE_SIZE_MASK ; 

__attribute__((used)) static void tg3_nvram_get_pagesize(struct tg3 *tp, u32 nvmcfg1)
{
	switch (nvmcfg1 & NVRAM_CFG1_5752PAGE_SIZE_MASK) {
	case FLASH_5752PAGE_SIZE_256:
		tp->nvram_pagesize = 256;
		break;
	case FLASH_5752PAGE_SIZE_512:
		tp->nvram_pagesize = 512;
		break;
	case FLASH_5752PAGE_SIZE_1K:
		tp->nvram_pagesize = 1024;
		break;
	case FLASH_5752PAGE_SIZE_2K:
		tp->nvram_pagesize = 2048;
		break;
	case FLASH_5752PAGE_SIZE_4K:
		tp->nvram_pagesize = 4096;
		break;
	case FLASH_5752PAGE_SIZE_264:
		tp->nvram_pagesize = 264;
		break;
	case FLASH_5752PAGE_SIZE_528:
		tp->nvram_pagesize = 528;
		break;
	}
}