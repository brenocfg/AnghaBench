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
struct st33zp24_spi_phy {int* tx_buf; int* rx_buf; int latency; struct spi_device* spi_device; } ;
struct spi_transfer {int* tx_buf; int* rx_buf; int len; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int LOCALITY0 ; 
 int TPM_DATA_FIFO ; 
 int /*<<< orphan*/  TPM_DUMMY_BYTE ; 
 int TPM_WRITE_DIRECTION ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int spi_sync_transfer (struct spi_device*,struct spi_transfer*,int) ; 
 int st33zp24_status_to_errno (int) ; 

__attribute__((used)) static int st33zp24_spi_send(void *phy_id, u8 tpm_register, u8 *tpm_data,
			     int tpm_size)
{
	int total_length = 0, ret = 0;
	struct st33zp24_spi_phy *phy = phy_id;
	struct spi_device *dev = phy->spi_device;
	struct spi_transfer spi_xfer = {
		.tx_buf = phy->tx_buf,
		.rx_buf = phy->rx_buf,
	};

	/* Pre-Header */
	phy->tx_buf[total_length++] = TPM_WRITE_DIRECTION | LOCALITY0;
	phy->tx_buf[total_length++] = tpm_register;

	if (tpm_size > 0 && tpm_register == TPM_DATA_FIFO) {
		phy->tx_buf[total_length++] = tpm_size >> 8;
		phy->tx_buf[total_length++] = tpm_size;
	}

	memcpy(&phy->tx_buf[total_length], tpm_data, tpm_size);
	total_length += tpm_size;

	memset(&phy->tx_buf[total_length], TPM_DUMMY_BYTE, phy->latency);

	spi_xfer.len = total_length + phy->latency;

	ret = spi_sync_transfer(dev, &spi_xfer, 1);
	if (ret == 0)
		ret = phy->rx_buf[total_length + phy->latency - 1];

	return st33zp24_status_to_errno(ret);
}