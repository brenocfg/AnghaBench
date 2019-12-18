#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;
struct loader_start {TYPE_1__ hdr; } ;
struct loader_msg_hdr {int dummy; } ;
struct ishtp_cl_data {int dummy; } ;
typedef  int /*<<< orphan*/  ldr_start_ack ;
typedef  int /*<<< orphan*/  ldr_start ;

/* Variables and functions */
 int /*<<< orphan*/  LOADER_CMD_START ; 
 int loader_cl_send (struct ishtp_cl_data*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct loader_start*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ish_fw_start(struct ishtp_cl_data *client_data)
{
	struct loader_start ldr_start;
	struct loader_msg_hdr ldr_start_ack;

	memset(&ldr_start, 0, sizeof(ldr_start));
	ldr_start.hdr.command = LOADER_CMD_START;
	return loader_cl_send(client_data,
			    (u8 *)&ldr_start,
			    sizeof(ldr_start),
			    (u8 *)&ldr_start_ack,
			    sizeof(ldr_start_ack));
}