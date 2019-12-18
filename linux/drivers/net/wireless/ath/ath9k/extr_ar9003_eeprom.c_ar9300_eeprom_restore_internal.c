#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;
struct TYPE_2__ {int txrxMask; } ;
struct ar9300_eeprom {TYPE_1__ baseEepHeader; } ;
typedef  int /*<<< orphan*/  (* eeprom_read_op ) (struct ath_hw*,int,int*,int) ;

/* Variables and functions */
 int AR9300_BASE_ADDR ; 
 int AR9300_BASE_ADDR_4K ; 
 int AR9300_BASE_ADDR_512 ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 int COMP_CKSUM_LEN ; 
 int COMP_HDR_LEN ; 
 int /*<<< orphan*/  EEPROM ; 
 int EEPROM_DATA_LEN_9485 ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MSTATE ; 
 scalar_t__ ar9300_check_eeprom_header (struct ath_hw*,int /*<<< orphan*/  (*) (struct ath_hw*,int,int*,int),int) ; 
 int /*<<< orphan*/  ar9300_check_header (int*) ; 
 int /*<<< orphan*/  ar9300_comp_cksum (int*,int) ; 
 int /*<<< orphan*/  ar9300_comp_hdr_unpack (int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  ar9300_compress_decision (struct ath_hw*,int,int,int,int*,int*,int,int) ; 
 int /*<<< orphan*/  ar9300_default ; 
 scalar_t__ ar9300_eeprom_restore_flash (struct ath_hw*,int*,int) ; 
 int /*<<< orphan*/  ar9300_read_eeprom (struct ath_hw*,int,int*,int) ; 
 int /*<<< orphan*/  ar9300_read_otp (struct ath_hw*,int,int*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_use_flash (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ar9300_eeprom_restore_internal(struct ath_hw *ah,
					  u8 *mptr, int mdata_size)
{
#define MDEFAULT 15
#define MSTATE 100
	int cptr;
	u8 *word;
	int code;
	int reference, length, major, minor;
	int osize;
	int it;
	u16 checksum, mchecksum;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ar9300_eeprom *eep;
	eeprom_read_op read;

	if (ath9k_hw_use_flash(ah)) {
		u8 txrx;

		if (ar9300_eeprom_restore_flash(ah, mptr, mdata_size))
			return -EIO;

		/* check if eeprom contains valid data */
		eep = (struct ar9300_eeprom *) mptr;
		txrx = eep->baseEepHeader.txrxMask;
		if (txrx != 0 && txrx != 0xff)
			return 0;
	}

	word = kzalloc(2048, GFP_KERNEL);
	if (!word)
		return -ENOMEM;

	memcpy(mptr, &ar9300_default, mdata_size);

	read = ar9300_read_eeprom;
	if (AR_SREV_9485(ah))
		cptr = AR9300_BASE_ADDR_4K;
	else if (AR_SREV_9330(ah))
		cptr = AR9300_BASE_ADDR_512;
	else
		cptr = AR9300_BASE_ADDR;
	ath_dbg(common, EEPROM, "Trying EEPROM access at Address 0x%04x\n",
		cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	cptr = AR9300_BASE_ADDR_4K;
	ath_dbg(common, EEPROM, "Trying EEPROM access at Address 0x%04x\n",
		cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	cptr = AR9300_BASE_ADDR_512;
	ath_dbg(common, EEPROM, "Trying EEPROM access at Address 0x%04x\n",
		cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	read = ar9300_read_otp;
	cptr = AR9300_BASE_ADDR;
	ath_dbg(common, EEPROM, "Trying OTP access at Address 0x%04x\n", cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	cptr = AR9300_BASE_ADDR_512;
	ath_dbg(common, EEPROM, "Trying OTP access at Address 0x%04x\n", cptr);
	if (ar9300_check_eeprom_header(ah, read, cptr))
		goto found;

	goto fail;

found:
	ath_dbg(common, EEPROM, "Found valid EEPROM data\n");

	for (it = 0; it < MSTATE; it++) {
		if (!read(ah, cptr, word, COMP_HDR_LEN))
			goto fail;

		if (!ar9300_check_header(word))
			break;

		ar9300_comp_hdr_unpack(word, &code, &reference,
				       &length, &major, &minor);
		ath_dbg(common, EEPROM,
			"Found block at %x: code=%d ref=%d length=%d major=%d minor=%d\n",
			cptr, code, reference, length, major, minor);
		if ((!AR_SREV_9485(ah) && length >= 1024) ||
		    (AR_SREV_9485(ah) && length > EEPROM_DATA_LEN_9485)) {
			ath_dbg(common, EEPROM, "Skipping bad header\n");
			cptr -= COMP_HDR_LEN;
			continue;
		}

		osize = length;
		read(ah, cptr, word, COMP_HDR_LEN + osize + COMP_CKSUM_LEN);
		checksum = ar9300_comp_cksum(&word[COMP_HDR_LEN], length);
		mchecksum = get_unaligned_le16(&word[COMP_HDR_LEN + osize]);
		ath_dbg(common, EEPROM, "checksum %x %x\n",
			checksum, mchecksum);
		if (checksum == mchecksum) {
			ar9300_compress_decision(ah, it, code, reference, mptr,
						 word, length, mdata_size);
		} else {
			ath_dbg(common, EEPROM,
				"skipping block with bad checksum\n");
		}
		cptr -= (COMP_HDR_LEN + osize + COMP_CKSUM_LEN);
	}

	kfree(word);
	return cptr;

fail:
	kfree(word);
	return -1;
}