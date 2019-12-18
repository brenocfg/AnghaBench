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
struct falcon_nic_data {int /*<<< orphan*/  xmac_poll_required; } ;
struct ef4_nic {int /*<<< orphan*/  phy_mode; struct falcon_nic_data* nic_data; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioexp_client; } ;

/* Variables and functions */
 scalar_t__ EF4_WORKAROUND_7884 (struct ef4_nic*) ; 
 int EIO ; 
 int ERANGE ; 
 int P1_AFE_PWD_LBN ; 
 int P1_DSP_PWD25_LBN ; 
 int /*<<< orphan*/  P1_IN ; 
 int /*<<< orphan*/  PHY_MODE_OFF ; 
 TYPE_1__* falcon_board (struct ef4_nic*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe4001_poweroff (struct ef4_nic*) ; 

__attribute__((used)) static int sfe4001_check_hw(struct ef4_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	s32 status;

	/* If XAUI link is up then do not monitor */
	if (EF4_WORKAROUND_7884(efx) && !nic_data->xmac_poll_required)
		return 0;

	/* Check the powered status of the PHY. Lack of power implies that
	 * the MAX6647 has shut down power to it, probably due to a temp.
	 * alarm. Reading the power status rather than the MAX6647 status
	 * directly because the later is read-to-clear and would thus
	 * start to power up the PHY again when polled, causing us to blip
	 * the power undesirably.
	 * We know we can read from the IO expander because we did
	 * it during power-on. Assume failure now is bad news. */
	status = i2c_smbus_read_byte_data(falcon_board(efx)->ioexp_client, P1_IN);
	if (status >= 0 &&
	    (status & ((1 << P1_AFE_PWD_LBN) | (1 << P1_DSP_PWD25_LBN))) != 0)
		return 0;

	/* Use board power control, not PHY power control */
	sfe4001_poweroff(efx);
	efx->phy_mode = PHY_MODE_OFF;

	return (status < 0) ? -EIO : -ERANGE;
}