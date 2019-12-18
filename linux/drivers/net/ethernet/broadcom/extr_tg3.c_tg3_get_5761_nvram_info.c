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
struct tg3 {int nvram_pagesize; void* nvram_size; int /*<<< orphan*/  nvram_jedecnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH ; 
#define  FLASH_5761VENDOR_ATMEL_ADB021D 143 
#define  FLASH_5761VENDOR_ATMEL_ADB041D 142 
#define  FLASH_5761VENDOR_ATMEL_ADB081D 141 
#define  FLASH_5761VENDOR_ATMEL_ADB161D 140 
#define  FLASH_5761VENDOR_ATMEL_MDB021D 139 
#define  FLASH_5761VENDOR_ATMEL_MDB041D 138 
#define  FLASH_5761VENDOR_ATMEL_MDB081D 137 
#define  FLASH_5761VENDOR_ATMEL_MDB161D 136 
#define  FLASH_5761VENDOR_ST_A_M45PE16 135 
#define  FLASH_5761VENDOR_ST_A_M45PE20 134 
#define  FLASH_5761VENDOR_ST_A_M45PE40 133 
#define  FLASH_5761VENDOR_ST_A_M45PE80 132 
#define  FLASH_5761VENDOR_ST_M_M45PE16 131 
#define  FLASH_5761VENDOR_ST_M_M45PE20 130 
#define  FLASH_5761VENDOR_ST_M_M45PE40 129 
#define  FLASH_5761VENDOR_ST_M_M45PE80 128 
 int /*<<< orphan*/  JEDEC_ATMEL ; 
 int /*<<< orphan*/  JEDEC_ST ; 
 int /*<<< orphan*/  NO_NVRAM_ADDR_TRANS ; 
 int /*<<< orphan*/  NVRAM_ADDR_LOCKOUT ; 
 int /*<<< orphan*/  NVRAM_BUFFERED ; 
 int /*<<< orphan*/  NVRAM_CFG1 ; 
 int NVRAM_CFG1_5752VENDOR_MASK ; 
 int /*<<< orphan*/  PROTECTED_NVRAM ; 
 void* TG3_NVRAM_SIZE_1MB ; 
 void* TG3_NVRAM_SIZE_256KB ; 
 void* TG3_NVRAM_SIZE_2MB ; 
 void* TG3_NVRAM_SIZE_512KB ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 void* tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_get_5761_nvram_info(struct tg3 *tp)
{
	u32 nvcfg1, protect = 0;

	nvcfg1 = tr32(NVRAM_CFG1);

	/* NVRAM protection for TPM */
	if (nvcfg1 & (1 << 27)) {
		tg3_flag_set(tp, PROTECTED_NVRAM);
		protect = 1;
	}

	nvcfg1 &= NVRAM_CFG1_5752VENDOR_MASK;
	switch (nvcfg1) {
	case FLASH_5761VENDOR_ATMEL_ADB021D:
	case FLASH_5761VENDOR_ATMEL_ADB041D:
	case FLASH_5761VENDOR_ATMEL_ADB081D:
	case FLASH_5761VENDOR_ATMEL_ADB161D:
	case FLASH_5761VENDOR_ATMEL_MDB021D:
	case FLASH_5761VENDOR_ATMEL_MDB041D:
	case FLASH_5761VENDOR_ATMEL_MDB081D:
	case FLASH_5761VENDOR_ATMEL_MDB161D:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);
		tp->nvram_pagesize = 256;
		break;
	case FLASH_5761VENDOR_ST_A_M45PE20:
	case FLASH_5761VENDOR_ST_A_M45PE40:
	case FLASH_5761VENDOR_ST_A_M45PE80:
	case FLASH_5761VENDOR_ST_A_M45PE16:
	case FLASH_5761VENDOR_ST_M_M45PE20:
	case FLASH_5761VENDOR_ST_M_M45PE40:
	case FLASH_5761VENDOR_ST_M_M45PE80:
	case FLASH_5761VENDOR_ST_M_M45PE16:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 256;
		break;
	}

	if (protect) {
		tp->nvram_size = tr32(NVRAM_ADDR_LOCKOUT);
	} else {
		switch (nvcfg1) {
		case FLASH_5761VENDOR_ATMEL_ADB161D:
		case FLASH_5761VENDOR_ATMEL_MDB161D:
		case FLASH_5761VENDOR_ST_A_M45PE16:
		case FLASH_5761VENDOR_ST_M_M45PE16:
			tp->nvram_size = TG3_NVRAM_SIZE_2MB;
			break;
		case FLASH_5761VENDOR_ATMEL_ADB081D:
		case FLASH_5761VENDOR_ATMEL_MDB081D:
		case FLASH_5761VENDOR_ST_A_M45PE80:
		case FLASH_5761VENDOR_ST_M_M45PE80:
			tp->nvram_size = TG3_NVRAM_SIZE_1MB;
			break;
		case FLASH_5761VENDOR_ATMEL_ADB041D:
		case FLASH_5761VENDOR_ATMEL_MDB041D:
		case FLASH_5761VENDOR_ST_A_M45PE40:
		case FLASH_5761VENDOR_ST_M_M45PE40:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			break;
		case FLASH_5761VENDOR_ATMEL_ADB021D:
		case FLASH_5761VENDOR_ATMEL_MDB021D:
		case FLASH_5761VENDOR_ST_A_M45PE20:
		case FLASH_5761VENDOR_ST_M_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			break;
		}
	}
}