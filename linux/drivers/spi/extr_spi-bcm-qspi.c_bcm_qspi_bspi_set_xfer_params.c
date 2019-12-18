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
typedef  int u8 ;
struct bcm_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI ; 
 int /*<<< orphan*/  BSPI_BITS_PER_CYCLE ; 
 int /*<<< orphan*/  BSPI_BITS_PER_PHASE ; 
 int /*<<< orphan*/  BSPI_CMD_AND_MODE_BYTE ; 
 int /*<<< orphan*/  BSPI_FLEX_MODE_ENABLE ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm_qspi_bspi_set_xfer_params(struct bcm_qspi *qspi, u8 cmd_byte,
					  int bpp, int bpc, int flex_mode)
{
	bcm_qspi_write(qspi, BSPI, BSPI_FLEX_MODE_ENABLE, 0);
	bcm_qspi_write(qspi, BSPI, BSPI_BITS_PER_CYCLE, bpc);
	bcm_qspi_write(qspi, BSPI, BSPI_BITS_PER_PHASE, bpp);
	bcm_qspi_write(qspi, BSPI, BSPI_CMD_AND_MODE_BYTE, cmd_byte);
	bcm_qspi_write(qspi, BSPI, BSPI_FLEX_MODE_ENABLE, flex_mode);
}