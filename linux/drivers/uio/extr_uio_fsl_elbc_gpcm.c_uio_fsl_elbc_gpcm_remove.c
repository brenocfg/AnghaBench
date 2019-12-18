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
struct uio_info {struct uio_info* name; TYPE_1__* mem; int /*<<< orphan*/  (* shutdown ) (struct uio_info*,int) ;struct uio_info* priv; } ;
struct platform_device {int dummy; } ;
struct fsl_elbc_gpcm {struct fsl_elbc_gpcm* name; TYPE_1__* mem; int /*<<< orphan*/  (* shutdown ) (struct uio_info*,int) ;struct fsl_elbc_gpcm* priv; } ;
struct TYPE_2__ {struct uio_info* name; int /*<<< orphan*/  internal_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 struct uio_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uio_info*,int) ; 
 int /*<<< orphan*/  uio_unregister_device (struct uio_info*) ; 

__attribute__((used)) static int uio_fsl_elbc_gpcm_remove(struct platform_device *pdev)
{
	struct uio_info *info = platform_get_drvdata(pdev);
	struct fsl_elbc_gpcm *priv = info->priv;

	platform_set_drvdata(pdev, NULL);
	uio_unregister_device(info);
	if (priv->shutdown)
		priv->shutdown(info, false);
	iounmap(info->mem[0].internal_addr);
	kfree(info->mem[0].name);
	kfree(info->name);
	kfree(info);
	kfree(priv);

	return 0;

}