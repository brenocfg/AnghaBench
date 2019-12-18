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
typedef  int /*<<< orphan*/  u8 ;
struct si2168_cmd {int wlen; int rlen; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void cmd_init(struct si2168_cmd *cmd, const u8 *buf, int wlen, int rlen)
{
	memcpy(cmd->args, buf, wlen);
	cmd->wlen = wlen;
	cmd->rlen = rlen;
}