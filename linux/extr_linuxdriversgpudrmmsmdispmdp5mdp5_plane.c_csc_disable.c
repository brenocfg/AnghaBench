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
typedef  int uint32_t ;
struct mdp5_kms {int dummy; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int MDP5_PIPE_OP_MODE_CSC_1_EN ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_OP_MODE (int) ; 
 int mdp5_read (struct mdp5_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csc_disable(struct mdp5_kms *mdp5_kms, enum mdp5_pipe pipe)
{
	uint32_t value = mdp5_read(mdp5_kms, REG_MDP5_PIPE_OP_MODE(pipe)) &
			 ~MDP5_PIPE_OP_MODE_CSC_1_EN;

	mdp5_write(mdp5_kms, REG_MDP5_PIPE_OP_MODE(pipe), value);
}