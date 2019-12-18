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
struct olpc_xo175_ec {int dummy; } ;
typedef  int /*<<< orphan*/  nonce ;

/* Variables and functions */
 int /*<<< orphan*/  olpc_xo175_ec_send_command (struct olpc_xo175_ec*,int*,int) ; 

__attribute__((used)) static void olpc_xo175_ec_read_packet(struct olpc_xo175_ec *priv)
{
	u8 nonce[] = {0xA5, 0x5A};

	olpc_xo175_ec_send_command(priv, nonce, sizeof(nonce));
}