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
struct hantro_dev {TYPE_1__* variant; } ;
struct TYPE_2__ {int /*<<< orphan*/  enc_fmts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_ENCODER ; 
 int hantro_add_func (struct hantro_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hantro_add_enc_func(struct hantro_dev *vpu)
{
	if (!vpu->variant->enc_fmts)
		return 0;

	return hantro_add_func(vpu, MEDIA_ENT_F_PROC_VIDEO_ENCODER);
}