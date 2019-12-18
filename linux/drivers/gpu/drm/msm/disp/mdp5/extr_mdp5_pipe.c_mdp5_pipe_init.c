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
typedef  void* uint32_t ;
struct mdp5_hw_pipe {int pipe; int /*<<< orphan*/  flush_mask; void* caps; void* reg_offset; int /*<<< orphan*/  name; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mdp5_hw_pipe* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mdp5_hw_pipe* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_ctl_flush_mask_pipe (int) ; 
 int /*<<< orphan*/  pipe2name (int) ; 

struct mdp5_hw_pipe *mdp5_pipe_init(enum mdp5_pipe pipe,
		uint32_t reg_offset, uint32_t caps)
{
	struct mdp5_hw_pipe *hwpipe;

	hwpipe = kzalloc(sizeof(*hwpipe), GFP_KERNEL);
	if (!hwpipe)
		return ERR_PTR(-ENOMEM);

	hwpipe->name = pipe2name(pipe);
	hwpipe->pipe = pipe;
	hwpipe->reg_offset = reg_offset;
	hwpipe->caps = caps;
	hwpipe->flush_mask = mdp_ctl_flush_mask_pipe(pipe);

	return hwpipe;
}