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
struct si_sm_data {int /*<<< orphan*/  obf_timeout; int /*<<< orphan*/  ibf_timeout; int /*<<< orphan*/  state; scalar_t__ read_pos; scalar_t__ write_pos; int /*<<< orphan*/  orig_write_count; int /*<<< orphan*/  write_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBF_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  KCS_WAIT_WRITE_START ; 
 int /*<<< orphan*/  KCS_WRITE_START ; 
 int /*<<< orphan*/  OBF_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  write_cmd (struct si_sm_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void restart_kcs_transaction(struct si_sm_data *kcs)
{
	kcs->write_count = kcs->orig_write_count;
	kcs->write_pos = 0;
	kcs->read_pos = 0;
	kcs->state = KCS_WAIT_WRITE_START;
	kcs->ibf_timeout = IBF_RETRY_TIMEOUT;
	kcs->obf_timeout = OBF_RETRY_TIMEOUT;
	write_cmd(kcs, KCS_WRITE_START);
}