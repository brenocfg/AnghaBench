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
struct dpu_encoder_phys_cmd {scalar_t__ serialize_wait4pp; } ;
struct dpu_encoder_phys {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int _dpu_encoder_phys_cmd_wait_for_ctl_start (struct dpu_encoder_phys*) ; 
 scalar_t__ dpu_encoder_phys_cmd_is_master (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_prepare_for_kickoff (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static int dpu_encoder_phys_cmd_wait_for_commit_done(
		struct dpu_encoder_phys *phys_enc)
{
	int rc = 0;
	struct dpu_encoder_phys_cmd *cmd_enc;

	if (!phys_enc)
		return -EINVAL;

	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	/* only required for master controller */
	if (dpu_encoder_phys_cmd_is_master(phys_enc))
		rc = _dpu_encoder_phys_cmd_wait_for_ctl_start(phys_enc);

	/* required for both controllers */
	if (!rc && cmd_enc->serialize_wait4pp)
		dpu_encoder_phys_cmd_prepare_for_kickoff(phys_enc);

	return rc;
}