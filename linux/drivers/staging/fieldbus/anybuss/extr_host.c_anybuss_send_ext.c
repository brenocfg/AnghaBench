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
struct anybuss_host {int dummy; } ;
struct anybuss_client {struct anybuss_host* host; } ;

/* Variables and functions */
 int _anybus_mbox_cmd (struct anybuss_host*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,size_t) ; 

int anybuss_send_ext(struct anybuss_client *client, u16 cmd_num,
		     const void *buf, size_t count)
{
	struct anybuss_host *cd = client->host;

	return _anybus_mbox_cmd(cd, cmd_num, true, NULL, 0, NULL, 0,
					buf, count);
}