#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {void* status; } ;
struct TYPE_4__ {void* sfr_value; void* sfr_address; void* sfr_page; } ;
struct TYPE_6__ {TYPE_2__ tdme_set_sfr_cnf; TYPE_1__ tdme_set_sfr_req; } ;
struct mac_message {int command_id; int length; TYPE_3__ pdata; } ;

/* Variables and functions */
 void* MAC_SYSTEM_ERROR ; 
 int SPI_IDLE ; 
 int SPI_TDME_SETSFR_CONFIRM ; 
 int SPI_TDME_SETSFR_REQUEST ; 
 int cascoda_api_downstream (int*,int,int*,void*) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u8 tdme_setsfr_request_sync(
	u8            sfr_page,
	u8            sfr_address,
	u8            sfr_value,
	void         *device_ref
)
{
	int ret;
	struct mac_message command, response;
	struct spi_device *spi = device_ref;

	command.command_id = SPI_TDME_SETSFR_REQUEST;
	command.length = 3;
	command.pdata.tdme_set_sfr_req.sfr_page    = sfr_page;
	command.pdata.tdme_set_sfr_req.sfr_address = sfr_address;
	command.pdata.tdme_set_sfr_req.sfr_value   = sfr_value;
	response.command_id = SPI_IDLE;
	ret = cascoda_api_downstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref
	);
	if (ret) {
		dev_crit(&spi->dev, "cascoda_api_downstream returned %d", ret);
		return MAC_SYSTEM_ERROR;
	}

	if (response.command_id != SPI_TDME_SETSFR_CONFIRM) {
		dev_crit(
			&spi->dev,
			"sync response to SPI_TDME_SETSFR_REQUEST was not SPI_TDME_SETSFR_CONFIRM, it was %d\n",
			response.command_id
		);
		return MAC_SYSTEM_ERROR;
	}

	return response.pdata.tdme_set_sfr_cnf.status;
}