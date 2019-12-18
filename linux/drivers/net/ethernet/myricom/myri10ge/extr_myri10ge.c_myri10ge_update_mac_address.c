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
typedef  int u8 ;
struct myri10ge_priv {int dummy; } ;
struct myri10ge_cmd {int data0; int data1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXGEFW_SET_MAC_ADDRESS ; 
 int myri10ge_send_cmd (struct myri10ge_priv*,int /*<<< orphan*/ ,struct myri10ge_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int myri10ge_update_mac_address(struct myri10ge_priv *mgp, u8 * addr)
{
	struct myri10ge_cmd cmd;
	int status;

	cmd.data0 = ((addr[0] << 24) | (addr[1] << 16)
		     | (addr[2] << 8) | addr[3]);

	cmd.data1 = ((addr[4] << 8) | (addr[5]));

	status = myri10ge_send_cmd(mgp, MXGEFW_SET_MAC_ADDRESS, &cmd, 0);
	return status;
}