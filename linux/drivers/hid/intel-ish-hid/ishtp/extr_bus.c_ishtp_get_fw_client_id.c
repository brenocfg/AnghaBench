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
struct ishtp_fw_client {int client_id; } ;

/* Variables and functions */

int ishtp_get_fw_client_id(struct ishtp_fw_client *fw_client)
{
	return fw_client->client_id;
}