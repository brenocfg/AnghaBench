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
struct ipw_rts_threshold {int /*<<< orphan*/  rts_threshold; } ;
struct ipw_priv {int dummy; } ;
typedef  int /*<<< orphan*/  rts_threshold ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_CMD_RTS_THRESHOLD ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int,struct ipw_rts_threshold*) ; 

__attribute__((used)) static int ipw_send_rts_threshold(struct ipw_priv *priv, u16 rts)
{
	struct ipw_rts_threshold rts_threshold = {
		.rts_threshold = cpu_to_le16(rts),
	};

	if (!priv) {
		IPW_ERROR("Invalid args\n");
		return -1;
	}

	return ipw_send_cmd_pdu(priv, IPW_CMD_RTS_THRESHOLD,
				sizeof(rts_threshold), &rts_threshold);
}