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
struct nvkm_secboot {int /*<<< orphan*/  subdev; } ;
struct ls_ucode_img {int dummy; } ;

/* Variables and functions */
 int ls_ucode_img_load_gr (int /*<<< orphan*/ *,int,struct ls_ucode_img*,char*) ; 

int
acr_ls_ucode_load_fecs(const struct nvkm_secboot *sb, int maxver,
		       struct ls_ucode_img *img)
{
	return ls_ucode_img_load_gr(&sb->subdev, maxver, img, "fecs");
}