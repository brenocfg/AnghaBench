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
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp5_kms {int /*<<< orphan*/  num_hwpipes; struct mdp5_hw_pipe** hwpipes; struct drm_device* dev; } ;
struct mdp5_hw_pipe {int /*<<< orphan*/  idx; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_ERR (struct mdp5_hw_pipe*) ; 
 int PTR_ERR (struct mdp5_hw_pipe*) ; 
 struct mdp5_hw_pipe* mdp5_pipe_init (int const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe2name (int const) ; 

__attribute__((used)) static int construct_pipes(struct mdp5_kms *mdp5_kms, int cnt,
		const enum mdp5_pipe *pipes, const uint32_t *offsets,
		uint32_t caps)
{
	struct drm_device *dev = mdp5_kms->dev;
	int i, ret;

	for (i = 0; i < cnt; i++) {
		struct mdp5_hw_pipe *hwpipe;

		hwpipe = mdp5_pipe_init(pipes[i], offsets[i], caps);
		if (IS_ERR(hwpipe)) {
			ret = PTR_ERR(hwpipe);
			DRM_DEV_ERROR(dev->dev, "failed to construct pipe for %s (%d)\n",
					pipe2name(pipes[i]), ret);
			return ret;
		}
		hwpipe->idx = mdp5_kms->num_hwpipes;
		mdp5_kms->hwpipes[mdp5_kms->num_hwpipes++] = hwpipe;
	}

	return 0;
}