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
union macaddr {scalar_t__* ieee_address; int /*<<< orphan*/  short_address; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct secspec {scalar_t__ security_level; } ;
struct mcps_data_request_pset {int dummy; } ;
struct TYPE_4__ {void** address; void** pan_id; scalar_t__ mode; } ;
struct TYPE_5__ {void** msdu; scalar_t__ tx_options; scalar_t__ msdu_handle; scalar_t__ msdu_length; TYPE_1__ dst; scalar_t__ src_addr_mode; } ;
struct TYPE_6__ {TYPE_2__ data_req; } ;
struct mac_message {int length; int /*<<< orphan*/  command_id; TYPE_3__ pdata; } ;

/* Variables and functions */
 void* LS_BYTE (int /*<<< orphan*/ ) ; 
 scalar_t__ MAC_MODE_NO_ADDR ; 
 scalar_t__ MAC_MODE_SHORT_ADDR ; 
 scalar_t__ MAC_SUCCESS ; 
 scalar_t__ MAC_SYSTEM_ERROR ; 
 int MAX_DATA_SIZE ; 
 void* MS_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MCPS_DATA_REQUEST ; 
 scalar_t__ ca8210_spi_transfer (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (void**,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static u8 mcps_data_request(
	u8               src_addr_mode,
	u8               dst_address_mode,
	u16              dst_pan_id,
	union macaddr   *dst_addr,
	u8               msdu_length,
	u8              *msdu,
	u8               msdu_handle,
	u8               tx_options,
	struct secspec  *security,
	void            *device_ref
)
{
	struct secspec *psec;
	struct mac_message command;

	command.command_id = SPI_MCPS_DATA_REQUEST;
	command.pdata.data_req.src_addr_mode = src_addr_mode;
	command.pdata.data_req.dst.mode = dst_address_mode;
	if (dst_address_mode != MAC_MODE_NO_ADDR) {
		command.pdata.data_req.dst.pan_id[0] = LS_BYTE(dst_pan_id);
		command.pdata.data_req.dst.pan_id[1] = MS_BYTE(dst_pan_id);
		if (dst_address_mode == MAC_MODE_SHORT_ADDR) {
			command.pdata.data_req.dst.address[0] = LS_BYTE(
				dst_addr->short_address
			);
			command.pdata.data_req.dst.address[1] = MS_BYTE(
				dst_addr->short_address
			);
		} else {   /* MAC_MODE_LONG_ADDR*/
			memcpy(
				command.pdata.data_req.dst.address,
				dst_addr->ieee_address,
				8
			);
		}
	}
	command.pdata.data_req.msdu_length = msdu_length;
	command.pdata.data_req.msdu_handle = msdu_handle;
	command.pdata.data_req.tx_options = tx_options;
	memcpy(command.pdata.data_req.msdu, msdu, msdu_length);
	psec = (struct secspec *)(command.pdata.data_req.msdu + msdu_length);
	command.length = sizeof(struct mcps_data_request_pset) -
		MAX_DATA_SIZE + msdu_length;
	if (!security || security->security_level == 0) {
		psec->security_level = 0;
		command.length += 1;
	} else {
		*psec = *security;
		command.length += sizeof(struct secspec);
	}

	if (ca8210_spi_transfer(device_ref, &command.command_id,
				command.length + 2))
		return MAC_SYSTEM_ERROR;

	return MAC_SUCCESS;
}