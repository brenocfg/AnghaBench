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
struct hantro_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_ENCODER ; 
 int /*<<< orphan*/  hantro_remove_func (struct hantro_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hantro_remove_enc_func(struct hantro_dev *vpu)
{
	hantro_remove_func(vpu, MEDIA_ENT_F_PROC_VIDEO_ENCODER);
}