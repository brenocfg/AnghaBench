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
struct fpgaimage {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bus_2byte ; 
 int /*<<< orphan*/  file ; 
 int gs_download_image (struct fpgaimage*,int /*<<< orphan*/ ) ; 
 int gs_load_image (struct fpgaimage*,int /*<<< orphan*/ ) ; 
 int gs_read_image (struct fpgaimage*) ; 
 int gs_release_image (struct fpgaimage*) ; 
 int gs_set_download_method (struct fpgaimage*) ; 
 int /*<<< orphan*/  kfree (struct fpgaimage*) ; 
 struct fpgaimage* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int gs_fpgaboot(void)
{
	int err;
	struct fpgaimage	*fimage;

	fimage = kmalloc(sizeof(*fimage), GFP_KERNEL);
	if (!fimage)
		return -ENOMEM;

	err = gs_load_image(fimage, file);
	if (err) {
		pr_err("gs_load_image error\n");
		goto err_out1;
	}

	err = gs_read_image(fimage);
	if (err) {
		pr_err("gs_read_image error\n");
		goto err_out2;
	}

	err = gs_set_download_method(fimage);
	if (err) {
		pr_err("gs_set_download_method error\n");
		goto err_out2;
	}

	err = gs_download_image(fimage, bus_2byte);
	if (err) {
		pr_err("gs_download_image error\n");
		goto err_out2;
	}

	err = gs_release_image(fimage);
	if (err) {
		pr_err("gs_release_image error\n");
		goto err_out1;
	}

	kfree(fimage);
	return 0;

err_out2:
	err = gs_release_image(fimage);
	if (err)
		pr_err("gs_release_image error\n");
err_out1:
	kfree(fimage);

	return err;
}