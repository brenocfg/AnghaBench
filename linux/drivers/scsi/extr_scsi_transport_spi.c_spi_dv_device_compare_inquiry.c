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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_device {int inquiry_len; } ;
typedef  enum spi_compare_returns { ____Placeholder_spi_compare_returns } spi_compare_returns ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int const INQUIRY ; 
 int /*<<< orphan*/  SDEV_QUIESCE ; 
 int SPI_COMPARE_FAILURE ; 
 int SPI_COMPARE_SUCCESS ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int spi_execute (struct scsi_device*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum spi_compare_returns
spi_dv_device_compare_inquiry(struct scsi_device *sdev, u8 *buffer,
			      u8 *ptr, const int retries)
{
	int r, result;
	const int len = sdev->inquiry_len;
	const char spi_inquiry[] = {
		INQUIRY, 0, 0, 0, len, 0
	};

	for (r = 0; r < retries; r++) {
		memset(ptr, 0, len);

		result = spi_execute(sdev, spi_inquiry, DMA_FROM_DEVICE,
				     ptr, len, NULL);
		
		if(result || !scsi_device_online(sdev)) {
			scsi_device_set_state(sdev, SDEV_QUIESCE);
			return SPI_COMPARE_FAILURE;
		}

		/* If we don't have the inquiry data already, the
		 * first read gets it */
		if (ptr == buffer) {
			ptr += len;
			--r;
			continue;
		}

		if (memcmp(buffer, ptr, len) != 0)
			/* failure */
			return SPI_COMPARE_FAILURE;
	}
	return SPI_COMPARE_SUCCESS;
}