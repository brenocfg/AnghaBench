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
struct tg3 {int nvram_pagesize; int nvram_size; int /*<<< orphan*/  nvram_jedecnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH ; 
#define  FLASH_5752VENDOR_ST_M45PE10 134 
#define  FLASH_5752VENDOR_ST_M45PE20 133 
#define  FLASH_5752VENDOR_ST_M45PE40 132 
#define  FLASH_5755VENDOR_ATMEL_FLASH_1 131 
#define  FLASH_5755VENDOR_ATMEL_FLASH_2 130 
#define  FLASH_5755VENDOR_ATMEL_FLASH_3 129 
#define  FLASH_5755VENDOR_ATMEL_FLASH_5 128 
 int /*<<< orphan*/  JEDEC_ATMEL ; 
 int /*<<< orphan*/  JEDEC_ST ; 
 int /*<<< orphan*/  NVRAM_BUFFERED ; 
 int /*<<< orphan*/  NVRAM_CFG1 ; 
 int NVRAM_CFG1_5752VENDOR_MASK ; 
 int /*<<< orphan*/  PROTECTED_NVRAM ; 
 int TG3_NVRAM_SIZE_128KB ; 
 int TG3_NVRAM_SIZE_256KB ; 
 int TG3_NVRAM_SIZE_512KB ; 
 int TG3_NVRAM_SIZE_64KB ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_get_5755_nvram_info(struct tg3 *tp)
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
	case FLASH_5755VENDOR_ATMEL_FLASH_1:
	case FLASH_5755VENDOR_ATMEL_FLASH_2:
	case FLASH_5755VENDOR_ATMEL_FLASH_3:
	case FLASH_5755VENDOR_ATMEL_FLASH_5:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 264;
		if (nvcfg1 == FLASH_5755VENDOR_ATMEL_FLASH_1 ||
		    nvcfg1 == FLASH_5755VENDOR_ATMEL_FLASH_5)
			tp->nvram_size = (protect ? 0x3e200 :
					  TG3_NVRAM_SIZE_512KB);
		else if (nvcfg1 == FLASH_5755VENDOR_ATMEL_FLASH_2)
			tp->nvram_size = (protect ? 0x1f200 :
					  TG3_NVRAM_SIZE_256KB);
		else
			tp->nvram_size = (protect ? 0x1f200 :
					  TG3_NVRAM_SIZE_128KB);
		break;
	case FLASH_5752VENDOR_ST_M45PE10:
	case FLASH_5752VENDOR_ST_M45PE20:
	case FLASH_5752VENDOR_ST_M45PE40:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 256;
		if (nvcfg1 == FLASH_5752VENDOR_ST_M45PE10)
			tp->nvram_size = (protect ?
					  TG3_NVRAM_SIZE_64KB :
					  TG3_NVRAM_SIZE_128KB);
		else if (nvcfg1 == FLASH_5752VENDOR_ST_M45PE20)
			tp->nvram_size = (protect ?
					  TG3_NVRAM_SIZE_64KB :
					  TG3_NVRAM_SIZE_256KB);
		else
			tp->nvram_size = (protect ?
					  TG3_NVRAM_SIZE_128KB :
					  TG3_NVRAM_SIZE_512KB);
		break;
	}
}