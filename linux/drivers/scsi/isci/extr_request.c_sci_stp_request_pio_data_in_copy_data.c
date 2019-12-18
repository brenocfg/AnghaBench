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
struct isci_stp_request {scalar_t__ pio_len; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_SUCCESS ; 
 scalar_t__ SCU_MAX_FRAME_BUFFER_SIZE ; 
 int sci_stp_request_pio_data_in_copy_data_buffer (struct isci_stp_request*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static enum sci_status sci_stp_request_pio_data_in_copy_data(
	struct isci_stp_request *stp_req,
	u8 *data_buffer)
{
	enum sci_status status;

	/*
	 * If there is less than 1K remaining in the transfer request
	 * copy just the data for the transfer */
	if (stp_req->pio_len < SCU_MAX_FRAME_BUFFER_SIZE) {
		status = sci_stp_request_pio_data_in_copy_data_buffer(
			stp_req, data_buffer, stp_req->pio_len);

		if (status == SCI_SUCCESS)
			stp_req->pio_len = 0;
	} else {
		/* We are transfering the whole frame so copy */
		status = sci_stp_request_pio_data_in_copy_data_buffer(
			stp_req, data_buffer, SCU_MAX_FRAME_BUFFER_SIZE);

		if (status == SCI_SUCCESS)
			stp_req->pio_len -= SCU_MAX_FRAME_BUFFER_SIZE;
	}

	return status;
}