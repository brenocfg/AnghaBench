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
struct opal_dev {int (* send_recv ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  cmd; int /*<<< orphan*/  comid; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_BUFFER_LENGTH ; 
 int /*<<< orphan*/  TCG_SECP_01 ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int opal_send_cmd(struct opal_dev *dev)
{
	return dev->send_recv(dev->data, dev->comid, TCG_SECP_01,
			      dev->cmd, IO_BUFFER_LENGTH,
			      true);
}