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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp_mst_encoder {int pipe; scalar_t__ connector; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 struct intel_dp_mst_encoder* enc_to_mst (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool intel_dp_mst_enc_get_hw_state(struct intel_encoder *encoder,
				      enum pipe *pipe)
{
	struct intel_dp_mst_encoder *intel_mst = enc_to_mst(&encoder->base);
	*pipe = intel_mst->pipe;
	if (intel_mst->connector)
		return true;
	return false;
}