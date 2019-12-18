#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  seq; } ;
struct carl9170_rsp {TYPE_1__ hdr; } ;
struct ar9170 {TYPE_2__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 scalar_t__ carl9170_check_sequence (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_handle_command_response (struct ar9170*,struct carl9170_rsp*,scalar_t__) ; 
 int /*<<< orphan*/  net_ratelimit () ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int const) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void carl9170_rx_untie_cmds(struct ar9170 *ar, const u8 *respbuf,
				   const unsigned int resplen)
{
	struct carl9170_rsp *cmd;
	int i = 0;

	while (i < resplen) {
		cmd = (void *) &respbuf[i];

		i += cmd->hdr.len + 4;
		if (unlikely(i > resplen))
			break;

		if (carl9170_check_sequence(ar, cmd->hdr.seq))
			break;

		carl9170_handle_command_response(ar, cmd, cmd->hdr.len + 4);
	}

	if (unlikely(i != resplen)) {
		if (!net_ratelimit())
			return;

		wiphy_err(ar->hw->wiphy, "malformed firmware trap:\n");
		print_hex_dump_bytes("rxcmd:", DUMP_PREFIX_OFFSET,
				     respbuf, resplen);
	}
}