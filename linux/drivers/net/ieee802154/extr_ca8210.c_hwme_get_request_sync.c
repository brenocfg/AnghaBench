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
typedef  scalar_t__ u8 ;
struct TYPE_5__ {scalar_t__ status; scalar_t__ hw_attribute_length; int /*<<< orphan*/  hw_attribute_value; } ;
struct TYPE_4__ {scalar_t__ hw_attribute; } ;
struct TYPE_6__ {TYPE_2__ hwme_get_cnf; TYPE_1__ hwme_get_req; } ;
struct mac_message {scalar_t__ command_id; int length; TYPE_3__ pdata; } ;

/* Variables and functions */
 scalar_t__ MAC_SUCCESS ; 
 scalar_t__ MAC_SYSTEM_ERROR ; 
 scalar_t__ SPI_HWME_GET_CONFIRM ; 
 scalar_t__ SPI_HWME_GET_REQUEST ; 
 scalar_t__ cascoda_api_downstream (scalar_t__*,int,scalar_t__*,void*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u8 hwme_get_request_sync(
	u8           hw_attribute,
	u8          *hw_attribute_length,
	u8          *hw_attribute_value,
	void        *device_ref
)
{
	struct mac_message command, response;

	command.command_id = SPI_HWME_GET_REQUEST;
	command.length = 1;
	command.pdata.hwme_get_req.hw_attribute = hw_attribute;

	if (cascoda_api_downstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref)) {
		return MAC_SYSTEM_ERROR;
	}

	if (response.command_id != SPI_HWME_GET_CONFIRM)
		return MAC_SYSTEM_ERROR;

	if (response.pdata.hwme_get_cnf.status == MAC_SUCCESS) {
		*hw_attribute_length =
			response.pdata.hwme_get_cnf.hw_attribute_length;
		memcpy(
			hw_attribute_value,
			response.pdata.hwme_get_cnf.hw_attribute_value,
			*hw_attribute_length
		);
	}

	return response.pdata.hwme_get_cnf.status;
}