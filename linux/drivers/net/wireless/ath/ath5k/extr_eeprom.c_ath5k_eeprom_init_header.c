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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ath5k_eeprom_info {scalar_t__ ee_version; int** ee_ob; int** ee_db; int ee_is_hb63; int ee_rfkill_pol; int ee_serdes; scalar_t__ ee_rfkill_pin; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {scalar_t__ ah_ee_version; int ah_mac_version; TYPE_1__ ah_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_EEPROM_ANT_GAIN (scalar_t__) ; 
 int /*<<< orphan*/  AR5K_EEPROM_HDR ; 
 int /*<<< orphan*/  AR5K_EEPROM_INFO (int) ; 
 int AR5K_EEPROM_INFO_BASE ; 
 int AR5K_EEPROM_INFO_CKSUM ; 
 int AR5K_EEPROM_INFO_MAX ; 
 int /*<<< orphan*/  AR5K_EEPROM_IS_HB63 ; 
 int /*<<< orphan*/  AR5K_EEPROM_MAGIC ; 
 int /*<<< orphan*/  AR5K_EEPROM_MISC0 ; 
 int /*<<< orphan*/  AR5K_EEPROM_MISC1 ; 
 int /*<<< orphan*/  AR5K_EEPROM_MISC2 ; 
 int /*<<< orphan*/  AR5K_EEPROM_MISC3 ; 
 int /*<<< orphan*/  AR5K_EEPROM_MISC4 ; 
 int /*<<< orphan*/  AR5K_EEPROM_MISC5 ; 
 int /*<<< orphan*/  AR5K_EEPROM_MISC6 ; 
 size_t AR5K_EEPROM_MODE_11B ; 
 size_t AR5K_EEPROM_MODE_11G ; 
 int /*<<< orphan*/  AR5K_EEPROM_OBDB0_2GHZ ; 
 int /*<<< orphan*/  AR5K_EEPROM_OBDB1_2GHZ ; 
 int /*<<< orphan*/  AR5K_EEPROM_PCIE_OFFSET ; 
 int AR5K_EEPROM_PCIE_SERDES_SECTION ; 
 int /*<<< orphan*/  AR5K_EEPROM_PROTECT ; 
 int /*<<< orphan*/  AR5K_EEPROM_READ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AR5K_EEPROM_READ_HDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_EEPROM_REG_DOMAIN ; 
 int /*<<< orphan*/  AR5K_EEPROM_RFKILL ; 
 int /*<<< orphan*/  AR5K_EEPROM_RFKILL_GPIO_SEL ; 
 int AR5K_EEPROM_RFKILL_POLARITY ; 
 int AR5K_EEPROM_SIZE_ENDLOC_SHIFT ; 
 int /*<<< orphan*/  AR5K_EEPROM_SIZE_LOWER ; 
 int /*<<< orphan*/  AR5K_EEPROM_SIZE_UPPER ; 
 int AR5K_EEPROM_SIZE_UPPER_MASK ; 
 int /*<<< orphan*/  AR5K_EEPROM_VERSION ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_0 ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_3 ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_0 ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_3 ; 
 scalar_t__ AR5K_EEPROM_VERSION_5_0 ; 
 scalar_t__ AR5K_REG_MS (int,int /*<<< orphan*/ ) ; 
 int AR5K_SREV_AR2425 ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,int,int,...) ; 
 int EIO ; 
 int /*<<< orphan*/  ee_ant_gain ; 
 int /*<<< orphan*/  ee_header ; 
 int /*<<< orphan*/  ee_magic ; 
 int /*<<< orphan*/  ee_misc0 ; 
 int /*<<< orphan*/  ee_misc1 ; 
 int /*<<< orphan*/  ee_misc2 ; 
 int /*<<< orphan*/  ee_misc3 ; 
 int /*<<< orphan*/  ee_misc4 ; 
 int /*<<< orphan*/  ee_misc5 ; 
 int /*<<< orphan*/  ee_misc6 ; 
 int /*<<< orphan*/  ee_protect ; 
 int /*<<< orphan*/  ee_regdomain ; 
 int /*<<< orphan*/  ee_version ; 

__attribute__((used)) static int
ath5k_eeprom_init_header(struct ath5k_hw *ah)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u16 val;
	u32 cksum, offset, eep_max = AR5K_EEPROM_INFO_MAX;

	/*
	 * Read values from EEPROM and store them in the capability structure
	 */
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MAGIC, ee_magic);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_PROTECT, ee_protect);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_REG_DOMAIN, ee_regdomain);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_VERSION, ee_version);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_HDR, ee_header);

	/* Return if we have an old EEPROM */
	if (ah->ah_ee_version < AR5K_EEPROM_VERSION_3_0)
		return 0;

	/*
	 * Validate the checksum of the EEPROM date. There are some
	 * devices with invalid EEPROMs.
	 */
	AR5K_EEPROM_READ(AR5K_EEPROM_SIZE_UPPER, val);
	if (val) {
		eep_max = (val & AR5K_EEPROM_SIZE_UPPER_MASK) <<
			   AR5K_EEPROM_SIZE_ENDLOC_SHIFT;
		AR5K_EEPROM_READ(AR5K_EEPROM_SIZE_LOWER, val);
		eep_max = (eep_max | val) - AR5K_EEPROM_INFO_BASE;

		/*
		 * Fail safe check to prevent stupid loops due
		 * to busted EEPROMs. XXX: This value is likely too
		 * big still, waiting on a better value.
		 */
		if (eep_max > (3 * AR5K_EEPROM_INFO_MAX)) {
			ATH5K_ERR(ah, "Invalid max custom EEPROM size: "
				  "%d (0x%04x) max expected: %d (0x%04x)\n",
				  eep_max, eep_max,
				  3 * AR5K_EEPROM_INFO_MAX,
				  3 * AR5K_EEPROM_INFO_MAX);
			return -EIO;
		}
	}

	for (cksum = 0, offset = 0; offset < eep_max; offset++) {
		AR5K_EEPROM_READ(AR5K_EEPROM_INFO(offset), val);
		cksum ^= val;
	}
	if (cksum != AR5K_EEPROM_INFO_CKSUM) {
		ATH5K_ERR(ah, "Invalid EEPROM "
			  "checksum: 0x%04x eep_max: 0x%04x (%s)\n",
			  cksum, eep_max,
			  eep_max == AR5K_EEPROM_INFO_MAX ?
				"default size" : "custom size");
		return -EIO;
	}

	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_ANT_GAIN(ah->ah_ee_version),
	    ee_ant_gain);

	if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0) {
		AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC0, ee_misc0);
		AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC1, ee_misc1);

		/* XXX: Don't know which versions include these two */
		AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC2, ee_misc2);

		if (ee->ee_version >= AR5K_EEPROM_VERSION_4_3)
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC3, ee_misc3);

		if (ee->ee_version >= AR5K_EEPROM_VERSION_5_0) {
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC4, ee_misc4);
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC5, ee_misc5);
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC6, ee_misc6);
		}
	}

	if (ah->ah_ee_version < AR5K_EEPROM_VERSION_3_3) {
		AR5K_EEPROM_READ(AR5K_EEPROM_OBDB0_2GHZ, val);
		ee->ee_ob[AR5K_EEPROM_MODE_11B][0] = val & 0x7;
		ee->ee_db[AR5K_EEPROM_MODE_11B][0] = (val >> 3) & 0x7;

		AR5K_EEPROM_READ(AR5K_EEPROM_OBDB1_2GHZ, val);
		ee->ee_ob[AR5K_EEPROM_MODE_11G][0] = val & 0x7;
		ee->ee_db[AR5K_EEPROM_MODE_11G][0] = (val >> 3) & 0x7;
	}

	AR5K_EEPROM_READ(AR5K_EEPROM_IS_HB63, val);

	if ((ah->ah_mac_version == (AR5K_SREV_AR2425 >> 4)) && val)
		ee->ee_is_hb63 = true;
	else
		ee->ee_is_hb63 = false;

	AR5K_EEPROM_READ(AR5K_EEPROM_RFKILL, val);
	ee->ee_rfkill_pin = (u8) AR5K_REG_MS(val, AR5K_EEPROM_RFKILL_GPIO_SEL);
	ee->ee_rfkill_pol = val & AR5K_EEPROM_RFKILL_POLARITY ? true : false;

	/* Check if PCIE_OFFSET points to PCIE_SERDES_SECTION
	 * and enable serdes programming if needed.
	 *
	 * XXX: Serdes values seem to be fixed so
	 * no need to read them here, we write them
	 * during ath5k_hw_init */
	AR5K_EEPROM_READ(AR5K_EEPROM_PCIE_OFFSET, val);
	ee->ee_serdes = (val == AR5K_EEPROM_PCIE_SERDES_SECTION) ?
							true : false;

	return 0;
}