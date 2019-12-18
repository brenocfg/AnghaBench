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
typedef  int /*<<< orphan*/  u32 ;
struct ar5523_tx_cmd {int olen; int /*<<< orphan*/  done; int /*<<< orphan*/  res; scalar_t__ odata; } ;
struct ar5523_cmd_hdr {int /*<<< orphan*/  code; int /*<<< orphan*/  len; } ;
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*,int,int) ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,int,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ar5523_read_reply(struct ar5523 *ar, struct ar5523_cmd_hdr *hdr,
			      struct ar5523_tx_cmd *cmd)
{
	int dlen, olen;
	__be32 *rp;

	dlen = be32_to_cpu(hdr->len) - sizeof(*hdr);

	if (dlen < 0) {
		WARN_ON(1);
		goto out;
	}

	ar5523_dbg(ar, "Code = %d len = %d\n", be32_to_cpu(hdr->code) & 0xff,
		   dlen);

	rp = (__be32 *)(hdr + 1);
	if (dlen >= sizeof(u32)) {
		olen = be32_to_cpu(rp[0]);
		dlen -= sizeof(u32);
		if (olen == 0) {
			/* convention is 0 =>'s one word */
			olen = sizeof(u32);
		}
	} else
		olen = 0;

	if (cmd->odata) {
		if (cmd->olen < olen) {
			ar5523_err(ar, "olen to small %d < %d\n",
				   cmd->olen, olen);
			cmd->olen = 0;
			cmd->res = -EOVERFLOW;
		} else {
			cmd->olen = olen;
			memcpy(cmd->odata, &rp[1], olen);
			cmd->res = 0;
		}
	}

out:
	complete(&cmd->done);
}