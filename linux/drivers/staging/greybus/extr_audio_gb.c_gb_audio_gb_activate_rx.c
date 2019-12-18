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
struct gb_audio_activate_rx_request {int /*<<< orphan*/  data_cport; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  GB_AUDIO_TYPE_ACTIVATE_RX ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_audio_activate_rx_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_audio_gb_activate_rx(struct gb_connection *connection,
			    u16 data_cport)
{
	struct gb_audio_activate_rx_request req;

	req.data_cport = cpu_to_le16(data_cport);

	return gb_operation_sync(connection, GB_AUDIO_TYPE_ACTIVATE_RX,
				 &req, sizeof(req), NULL, 0);
}