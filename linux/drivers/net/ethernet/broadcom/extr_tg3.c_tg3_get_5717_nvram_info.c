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
#define  FLASH_5717VENDOR_ATMEL_45USPT 146 
#define  FLASH_5717VENDOR_ATMEL_ADB011B 145 
#define  FLASH_5717VENDOR_ATMEL_ADB011D 144 
#define  FLASH_5717VENDOR_ATMEL_ADB021B 143 
#define  FLASH_5717VENDOR_ATMEL_ADB021D 142 
#define  FLASH_5717VENDOR_ATMEL_EEPROM 141 
#define  FLASH_5717VENDOR_ATMEL_MDB011D 140 
#define  FLASH_5717VENDOR_ATMEL_MDB021D 139 
#define  FLASH_5717VENDOR_MICRO_EEPROM 138 
#define  FLASH_5717VENDOR_ST_25USPT 137 
#define  FLASH_5717VENDOR_ST_45USPT 136 
#define  FLASH_5717VENDOR_ST_A_M25PE10 135 
#define  FLASH_5717VENDOR_ST_A_M25PE20 134 
#define  FLASH_5717VENDOR_ST_A_M45PE10 133 
#define  FLASH_5717VENDOR_ST_A_M45PE20 132 
#define  FLASH_5717VENDOR_ST_M_M25PE10 131 
#define  FLASH_5717VENDOR_ST_M_M25PE20 130 
#define  FLASH_5717VENDOR_ST_M_M45PE10 129 
#define  FLASH_5717VENDOR_ST_M_M45PE20 128 
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
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_nvram_get_pagesize (struct tg3*,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_get_5717_nvram_info(struct tg3 *tp)
{
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);

	switch (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) {
	case FLASH_5717VENDOR_ATMEL_EEPROM:
	case FLASH_5717VENDOR_MICRO_EEPROM:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		return;
	case FLASH_5717VENDOR_ATMEL_MDB011D:
	case FLASH_5717VENDOR_ATMEL_ADB011B:
	case FLASH_5717VENDOR_ATMEL_ADB011D:
	case FLASH_5717VENDOR_ATMEL_MDB021D:
	case FLASH_5717VENDOR_ATMEL_ADB021B:
	case FLASH_5717VENDOR_ATMEL_ADB021D:
	case FLASH_5717VENDOR_ATMEL_45USPT:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		switch (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) {
		case FLASH_5717VENDOR_ATMEL_MDB021D:
			/* Detect size with tg3_nvram_get_size() */
			break;
		case FLASH_5717VENDOR_ATMEL_ADB021B:
		case FLASH_5717VENDOR_ATMEL_ADB021D:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			break;
		default:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			break;
		}
		break;
	case FLASH_5717VENDOR_ST_M_M25PE10:
	case FLASH_5717VENDOR_ST_A_M25PE10:
	case FLASH_5717VENDOR_ST_M_M45PE10:
	case FLASH_5717VENDOR_ST_A_M45PE10:
	case FLASH_5717VENDOR_ST_M_M25PE20:
	case FLASH_5717VENDOR_ST_A_M25PE20:
	case FLASH_5717VENDOR_ST_M_M45PE20:
	case FLASH_5717VENDOR_ST_A_M45PE20:
	case FLASH_5717VENDOR_ST_25USPT:
	case FLASH_5717VENDOR_ST_45USPT:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		switch (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) {
		case FLASH_5717VENDOR_ST_M_M25PE20:
		case FLASH_5717VENDOR_ST_M_M45PE20:
			/* Detect size with tg3_nvram_get_size() */
			break;
		case FLASH_5717VENDOR_ST_A_M25PE20:
		case FLASH_5717VENDOR_ST_A_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			break;
		default:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
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