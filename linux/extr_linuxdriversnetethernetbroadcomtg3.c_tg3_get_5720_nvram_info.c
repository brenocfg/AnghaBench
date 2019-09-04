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
struct tg3 {int nvram_pagesize; int nvram_size; void* nvram_jedecnum; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5762 ; 
 int ATMEL_AT24C02_CHIP_SIZE ; 
 int ATMEL_AT24C512_CHIP_SIZE ; 
 int AUTOSENSE_DEVID ; 
 int AUTOSENSE_DEVID_MASK ; 
 int AUTOSENSE_SIZE_IN_MB ; 
 int /*<<< orphan*/  FLASH ; 
#define  FLASH_5720VENDOR_ATMEL_45USPT 166 
#define  FLASH_5720VENDOR_A_ATMEL_DB011B 165 
#define  FLASH_5720VENDOR_A_ATMEL_DB011D 164 
#define  FLASH_5720VENDOR_A_ATMEL_DB021B 163 
#define  FLASH_5720VENDOR_A_ATMEL_DB021D 162 
#define  FLASH_5720VENDOR_A_ATMEL_DB041B 161 
#define  FLASH_5720VENDOR_A_ATMEL_DB041D 160 
#define  FLASH_5720VENDOR_A_ATMEL_DB081D 159 
#define  FLASH_5720VENDOR_A_ST_M25PE10 158 
#define  FLASH_5720VENDOR_A_ST_M25PE20 157 
#define  FLASH_5720VENDOR_A_ST_M25PE40 156 
#define  FLASH_5720VENDOR_A_ST_M25PE80 155 
#define  FLASH_5720VENDOR_A_ST_M45PE10 154 
#define  FLASH_5720VENDOR_A_ST_M45PE20 153 
#define  FLASH_5720VENDOR_A_ST_M45PE40 152 
#define  FLASH_5720VENDOR_A_ST_M45PE80 151 
#define  FLASH_5720VENDOR_M_ATMEL_DB011D 150 
#define  FLASH_5720VENDOR_M_ATMEL_DB021D 149 
#define  FLASH_5720VENDOR_M_ATMEL_DB041D 148 
#define  FLASH_5720VENDOR_M_ATMEL_DB081D 147 
#define  FLASH_5720VENDOR_M_ST_M25PE10 146 
#define  FLASH_5720VENDOR_M_ST_M25PE20 145 
#define  FLASH_5720VENDOR_M_ST_M25PE40 144 
#define  FLASH_5720VENDOR_M_ST_M25PE80 143 
#define  FLASH_5720VENDOR_M_ST_M45PE10 142 
#define  FLASH_5720VENDOR_M_ST_M45PE20 141 
#define  FLASH_5720VENDOR_M_ST_M45PE40 140 
#define  FLASH_5720VENDOR_M_ST_M45PE80 139 
#define  FLASH_5720VENDOR_ST_25USPT 138 
#define  FLASH_5720VENDOR_ST_45USPT 137 
#define  FLASH_5720_EEPROM_HD 136 
#define  FLASH_5720_EEPROM_LD 135 
#define  FLASH_5762_EEPROM_HD 134 
#define  FLASH_5762_EEPROM_LD 133 
#define  FLASH_5762_MX25L_100 132 
#define  FLASH_5762_MX25L_160_320 131 
#define  FLASH_5762_MX25L_200 130 
#define  FLASH_5762_MX25L_400 129 
#define  FLASH_5762_MX25L_800 128 
 void* JEDEC_ATMEL ; 
 void* JEDEC_MACRONIX ; 
 void* JEDEC_ST ; 
 int /*<<< orphan*/  NO_NVRAM ; 
 int /*<<< orphan*/  NO_NVRAM_ADDR_TRANS ; 
 int /*<<< orphan*/  NVRAM_AUTOSENSE_STATUS ; 
 int /*<<< orphan*/  NVRAM_BUFFERED ; 
 int /*<<< orphan*/  NVRAM_CFG1 ; 
 int NVRAM_CFG1_5752VENDOR_MASK ; 
 int NVRAM_CFG1_5762VENDOR_MASK ; 
 int NVRAM_CFG1_COMPAT_BYPASS ; 
 int TG3_EEPROM_MAGIC ; 
 int TG3_EEPROM_MAGIC_FW ; 
 int TG3_EEPROM_MAGIC_FW_MSK ; 
 void* TG3_NVRAM_SIZE_128KB ; 
 void* TG3_NVRAM_SIZE_1MB ; 
 void* TG3_NVRAM_SIZE_256KB ; 
 void* TG3_NVRAM_SIZE_512KB ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_nvram_get_pagesize (struct tg3*,int) ; 
 scalar_t__ tg3_nvram_read (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_get_5720_nvram_info(struct tg3 *tp)
{
	u32 nvcfg1, nvmpinstrp, nv_status;

	nvcfg1 = tr32(NVRAM_CFG1);
	nvmpinstrp = nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK;

	if (tg3_asic_rev(tp) == ASIC_REV_5762) {
		if (!(nvcfg1 & NVRAM_CFG1_5762VENDOR_MASK)) {
			tg3_flag_set(tp, NO_NVRAM);
			return;
		}

		switch (nvmpinstrp) {
		case FLASH_5762_MX25L_100:
		case FLASH_5762_MX25L_200:
		case FLASH_5762_MX25L_400:
		case FLASH_5762_MX25L_800:
		case FLASH_5762_MX25L_160_320:
			tp->nvram_pagesize = 4096;
			tp->nvram_jedecnum = JEDEC_MACRONIX;
			tg3_flag_set(tp, NVRAM_BUFFERED);
			tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);
			tg3_flag_set(tp, FLASH);
			nv_status = tr32(NVRAM_AUTOSENSE_STATUS);
			tp->nvram_size =
				(1 << (nv_status >> AUTOSENSE_DEVID &
						AUTOSENSE_DEVID_MASK)
					<< AUTOSENSE_SIZE_IN_MB);
			return;

		case FLASH_5762_EEPROM_HD:
			nvmpinstrp = FLASH_5720_EEPROM_HD;
			break;
		case FLASH_5762_EEPROM_LD:
			nvmpinstrp = FLASH_5720_EEPROM_LD;
			break;
		case FLASH_5720VENDOR_M_ST_M45PE20:
			/* This pinstrap supports multiple sizes, so force it
			 * to read the actual size from location 0xf0.
			 */
			nvmpinstrp = FLASH_5720VENDOR_ST_45USPT;
			break;
		}
	}

	switch (nvmpinstrp) {
	case FLASH_5720_EEPROM_HD:
	case FLASH_5720_EEPROM_LD:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		if (nvmpinstrp == FLASH_5720_EEPROM_HD)
			tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;
		else
			tp->nvram_pagesize = ATMEL_AT24C02_CHIP_SIZE;
		return;
	case FLASH_5720VENDOR_M_ATMEL_DB011D:
	case FLASH_5720VENDOR_A_ATMEL_DB011B:
	case FLASH_5720VENDOR_A_ATMEL_DB011D:
	case FLASH_5720VENDOR_M_ATMEL_DB021D:
	case FLASH_5720VENDOR_A_ATMEL_DB021B:
	case FLASH_5720VENDOR_A_ATMEL_DB021D:
	case FLASH_5720VENDOR_M_ATMEL_DB041D:
	case FLASH_5720VENDOR_A_ATMEL_DB041B:
	case FLASH_5720VENDOR_A_ATMEL_DB041D:
	case FLASH_5720VENDOR_M_ATMEL_DB081D:
	case FLASH_5720VENDOR_A_ATMEL_DB081D:
	case FLASH_5720VENDOR_ATMEL_45USPT:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		switch (nvmpinstrp) {
		case FLASH_5720VENDOR_M_ATMEL_DB021D:
		case FLASH_5720VENDOR_A_ATMEL_DB021B:
		case FLASH_5720VENDOR_A_ATMEL_DB021D:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			break;
		case FLASH_5720VENDOR_M_ATMEL_DB041D:
		case FLASH_5720VENDOR_A_ATMEL_DB041B:
		case FLASH_5720VENDOR_A_ATMEL_DB041D:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			break;
		case FLASH_5720VENDOR_M_ATMEL_DB081D:
		case FLASH_5720VENDOR_A_ATMEL_DB081D:
			tp->nvram_size = TG3_NVRAM_SIZE_1MB;
			break;
		default:
			if (tg3_asic_rev(tp) != ASIC_REV_5762)
				tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			break;
		}
		break;
	case FLASH_5720VENDOR_M_ST_M25PE10:
	case FLASH_5720VENDOR_M_ST_M45PE10:
	case FLASH_5720VENDOR_A_ST_M25PE10:
	case FLASH_5720VENDOR_A_ST_M45PE10:
	case FLASH_5720VENDOR_M_ST_M25PE20:
	case FLASH_5720VENDOR_M_ST_M45PE20:
	case FLASH_5720VENDOR_A_ST_M25PE20:
	case FLASH_5720VENDOR_A_ST_M45PE20:
	case FLASH_5720VENDOR_M_ST_M25PE40:
	case FLASH_5720VENDOR_M_ST_M45PE40:
	case FLASH_5720VENDOR_A_ST_M25PE40:
	case FLASH_5720VENDOR_A_ST_M45PE40:
	case FLASH_5720VENDOR_M_ST_M25PE80:
	case FLASH_5720VENDOR_M_ST_M45PE80:
	case FLASH_5720VENDOR_A_ST_M25PE80:
	case FLASH_5720VENDOR_A_ST_M45PE80:
	case FLASH_5720VENDOR_ST_25USPT:
	case FLASH_5720VENDOR_ST_45USPT:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		switch (nvmpinstrp) {
		case FLASH_5720VENDOR_M_ST_M25PE20:
		case FLASH_5720VENDOR_M_ST_M45PE20:
		case FLASH_5720VENDOR_A_ST_M25PE20:
		case FLASH_5720VENDOR_A_ST_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			break;
		case FLASH_5720VENDOR_M_ST_M25PE40:
		case FLASH_5720VENDOR_M_ST_M45PE40:
		case FLASH_5720VENDOR_A_ST_M25PE40:
		case FLASH_5720VENDOR_A_ST_M45PE40:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			break;
		case FLASH_5720VENDOR_M_ST_M25PE80:
		case FLASH_5720VENDOR_M_ST_M45PE80:
		case FLASH_5720VENDOR_A_ST_M25PE80:
		case FLASH_5720VENDOR_A_ST_M45PE80:
			tp->nvram_size = TG3_NVRAM_SIZE_1MB;
			break;
		default:
			if (tg3_asic_rev(tp) != ASIC_REV_5762)
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

	if (tg3_asic_rev(tp) == ASIC_REV_5762) {
		u32 val;

		if (tg3_nvram_read(tp, 0, &val))
			return;

		if (val != TG3_EEPROM_MAGIC &&
		    (val & TG3_EEPROM_MAGIC_FW_MSK) != TG3_EEPROM_MAGIC_FW)
			tg3_flag_set(tp, NO_NVRAM);
	}
}