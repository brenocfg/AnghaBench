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
struct tg3 {int nvram_pagesize; void* nvram_size; void* nvram_jedecnum; } ;

/* Variables and functions */
 int ATMEL_AT24C512_CHIP_SIZE ; 
 int /*<<< orphan*/  FLASH ; 
#define  FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED 139 
#define  FLASH_5752VENDOR_ST_M45PE10 138 
#define  FLASH_5752VENDOR_ST_M45PE20 137 
#define  FLASH_5752VENDOR_ST_M45PE40 136 
#define  FLASH_57780VENDOR_ATMEL_AT45DB011B 135 
#define  FLASH_57780VENDOR_ATMEL_AT45DB011D 134 
#define  FLASH_57780VENDOR_ATMEL_AT45DB021B 133 
#define  FLASH_57780VENDOR_ATMEL_AT45DB021D 132 
#define  FLASH_57780VENDOR_ATMEL_AT45DB041B 131 
#define  FLASH_57780VENDOR_ATMEL_AT45DB041D 130 
#define  FLASH_5787VENDOR_ATMEL_EEPROM_376KHZ 129 
#define  FLASH_5787VENDOR_MICRO_EEPROM_376KHZ 128 
 void* JEDEC_ATMEL ; 
 void* JEDEC_ST ; 
 int /*<<< orphan*/  NO_NVRAM ; 
 int /*<<< orphan*/  NO_NVRAM_ADDR_TRANS ; 
 int /*<<< orphan*/  NVRAM_BUFFERED ; 
 int /*<<< orphan*/  NVRAM_CFG1 ; 
 int NVRAM_CFG1_5752VENDOR_MASK ; 
 int NVRAM_CFG1_COMPAT_BYPASS ; 
 void* TG3_NVRAM_SIZE_128KB ; 
 void* TG3_NVRAM_SIZE_256KB ; 
 void* TG3_NVRAM_SIZE_512KB ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_nvram_get_pagesize (struct tg3*,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_get_57780_nvram_info(struct tg3 *tp)
{
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);

	switch (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) {
	case FLASH_5787VENDOR_ATMEL_EEPROM_376KHZ:
	case FLASH_5787VENDOR_MICRO_EEPROM_376KHZ:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		return;
	case FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED:
	case FLASH_57780VENDOR_ATMEL_AT45DB011D:
	case FLASH_57780VENDOR_ATMEL_AT45DB011B:
	case FLASH_57780VENDOR_ATMEL_AT45DB021D:
	case FLASH_57780VENDOR_ATMEL_AT45DB021B:
	case FLASH_57780VENDOR_ATMEL_AT45DB041D:
	case FLASH_57780VENDOR_ATMEL_AT45DB041B:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		switch (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) {
		case FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED:
		case FLASH_57780VENDOR_ATMEL_AT45DB011D:
		case FLASH_57780VENDOR_ATMEL_AT45DB011B:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			break;
		case FLASH_57780VENDOR_ATMEL_AT45DB021D:
		case FLASH_57780VENDOR_ATMEL_AT45DB021B:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			break;
		case FLASH_57780VENDOR_ATMEL_AT45DB041D:
		case FLASH_57780VENDOR_ATMEL_AT45DB041B:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			break;
		}
		break;
	case FLASH_5752VENDOR_ST_M45PE10:
	case FLASH_5752VENDOR_ST_M45PE20:
	case FLASH_5752VENDOR_ST_M45PE40:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		switch (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) {
		case FLASH_5752VENDOR_ST_M45PE10:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			break;
		case FLASH_5752VENDOR_ST_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			break;
		case FLASH_5752VENDOR_ST_M45PE40:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			break;
		}
		break;
	default:
		tg3_flag_set(tp, NO_NVRAM);
		return;
	}

	tg3_nvram_get_pagesize(tp, nvcfg1);
	if (tp->nvram_pagesize != 264 && tp->nvram_pagesize != 528)
		tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);
}