#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vpu_run {int /*<<< orphan*/  enc_capability; int /*<<< orphan*/  dec_capability; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  signaled; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  enc_capability; int /*<<< orphan*/  dec_capability; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  signaled; } ;
struct mtk_vpu {TYPE_1__ run; } ;

/* Variables and functions */
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vpu_init_ipi_handler(void *data, unsigned int len, void *priv)
{
	struct mtk_vpu *vpu = (struct mtk_vpu *)priv;
	struct vpu_run *run = (struct vpu_run *)data;

	vpu->run.signaled = run->signaled;
	strscpy(vpu->run.fw_ver, run->fw_ver, sizeof(vpu->run.fw_ver));
	vpu->run.dec_capability = run->dec_capability;
	vpu->run.enc_capability = run->enc_capability;
	wake_up_interruptible(&vpu->run.wq);
}