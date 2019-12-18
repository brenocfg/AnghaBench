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
typedef  int /*<<< orphan*/  u16 ;
struct gb_connection {int dummy; } ;
struct gb_audio_set_rx_data_size_request {void* size; void* data_cport; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  GB_AUDIO_TYPE_SET_RX_DATA_SIZE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_audio_set_rx_data_size_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_audio_gb_set_rx_data_size(struct gb_connection *connection,
				 u16 data_cport, u16 size)
{
	struct gb_audio_set_rx_data_size_request req;

	req.data_cport = cpu_to_le16(data_cport);
	req.size = cpu_to_le16(size);

	return gb_operation_sync(connection, GB_AUDIO_TYPE_SET_RX_DATA_SIZE,
				 &req, sizeof(req), NULL, 0);
}