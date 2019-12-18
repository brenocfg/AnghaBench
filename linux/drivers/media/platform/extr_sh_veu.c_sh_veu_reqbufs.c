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
struct v4l2_requestbuffers {int /*<<< orphan*/  type; } ;
struct sh_veu_file {struct sh_veu_dev* veu_dev; } ;
struct sh_veu_dev {int /*<<< orphan*/  m2m_ctx; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int sh_veu_context_init (struct sh_veu_dev*) ; 
 int sh_veu_stream_init (struct sh_veu_dev*,struct sh_veu_file*,int /*<<< orphan*/ ) ; 
 int v4l2_m2m_reqbufs (struct file*,int /*<<< orphan*/ ,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int sh_veu_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *reqbufs)
{
	struct sh_veu_file *veu_file = priv;
	struct sh_veu_dev *veu = veu_file->veu_dev;
	int ret = sh_veu_context_init(veu);
	if (ret < 0)
		return ret;

	ret = sh_veu_stream_init(veu, veu_file, reqbufs->type);
	if (ret < 0)
		return ret;

	return v4l2_m2m_reqbufs(file, veu->m2m_ctx, reqbufs);
}