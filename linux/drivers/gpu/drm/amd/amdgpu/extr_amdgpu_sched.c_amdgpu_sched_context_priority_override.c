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
struct fd {int /*<<< orphan*/  file; } ;
struct amdgpu_fpriv {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_ctx {int dummy; } ;
typedef  enum drm_sched_priority { ____Placeholder_drm_sched_priority } drm_sched_priority ;

/* Variables and functions */
 int EINVAL ; 
 struct amdgpu_ctx* amdgpu_ctx_get (struct amdgpu_fpriv*,unsigned int) ; 
 int /*<<< orphan*/  amdgpu_ctx_priority_override (struct amdgpu_ctx*,int) ; 
 int /*<<< orphan*/  amdgpu_ctx_put (struct amdgpu_ctx*) ; 
 int amdgpu_file_to_fpriv (int /*<<< orphan*/ ,struct amdgpu_fpriv**) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 

__attribute__((used)) static int amdgpu_sched_context_priority_override(struct amdgpu_device *adev,
						  int fd,
						  unsigned ctx_id,
						  enum drm_sched_priority priority)
{
	struct fd f = fdget(fd);
	struct amdgpu_fpriv *fpriv;
	struct amdgpu_ctx *ctx;
	int r;

	if (!f.file)
		return -EINVAL;

	r = amdgpu_file_to_fpriv(f.file, &fpriv);
	if (r) {
		fdput(f);
		return r;
	}

	ctx = amdgpu_ctx_get(fpriv, ctx_id);

	if (!ctx) {
		fdput(f);
		return -EINVAL;
	}

	amdgpu_ctx_priority_override(ctx, priority);
	amdgpu_ctx_put(ctx);
	fdput(f);

	return 0;
}