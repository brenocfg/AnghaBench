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
struct tg3 {int nvram_pagesize; void* nvram_jedecnum; } ;

/* Variables and functions */
 int ATMEL_AT24C512_CHIP_SIZE ; 
 int /*<<< orphan*/  FLASH ; 
#define  FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED 138 
#define  FLASH_5752VENDOR_ST_M45PE10 137 
#define  FLASH_5752VENDOR_ST_M45PE20 136 
#define  FLASH_5752VENDOR_ST_M45PE40 135 
#define  FLASH_5755VENDOR_ATMEL_FLASH_1 134 
#define  FLASH_5755VENDOR_ATMEL_FLASH_2 133 
#define  FLASH_5755VENDOR_ATMEL_FLASH_3 132 
#define  FLASH_5787VENDOR_ATMEL_EEPROM_376KHZ 131 
#define  FLASH_5787VENDOR_ATMEL_EEPROM_64KHZ 130 
#define  FLASH_5787VENDOR_MICRO_EEPROM_376KHZ 129 
#define  FLASH_5787VENDOR_MICRO_EEPROM_64KHZ 128 
 void* JEDEC_ATMEL ; 
 void* JEDEC_ST ; 
 int /*<<< orphan*/  NVRAM_BUFFERED ; 
 int /*<<< orphan*/  NVRAM_CFG1 ; 
 int NVRAM_CFG1_5752VENDOR_MASK ; 
 int NVRAM_CFG1_COMPAT_BYPASS ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_get_5787_nvram_info(struct tg3 *tp)
{
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);

	switch (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) {
	case FLASH_5787VENDOR_ATMEL_EEPROM_64KHZ:
	case FLASH_5787VENDOR_ATMEL_EEPROM_376KHZ:
	case FLASH_5787VENDOR_MICRO_EEPROM_64KHZ:
	case FLASH_5787VENDOR_MICRO_EEPROM_376KHZ:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		break;
	case FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED:
	case FLASH_5755VENDOR_ATMEL_FLASH_1:
	case FLASH_5755VENDOR_ATMEL_FLASH_2:
	case FLASH_5755VENDOR_ATMEL_FLASH_3:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 264;
		break;
	case FLASH_5752VENDOR_ST_M45PE10:
	case FLASH_5752VENDOR_ST_M45PE20:
	case FLASH_5752VENDOR_ST_M45PE40:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 256;
		break;
	}
}