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
struct fw_state {int /*<<< orphan*/  status; int /*<<< orphan*/  completion; } ;
struct fw_priv {struct fw_state fw_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fw_state_init(struct fw_priv *fw_priv)
{
	struct fw_state *fw_st = &fw_priv->fw_st;

	init_completion(&fw_st->completion);
	fw_st->status = FW_STATUS_UNKNOWN;
}