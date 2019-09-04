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
struct sh_mtu2_device {int num_channels; int /*<<< orphan*/  clk; int /*<<< orphan*/  mapbase; int /*<<< orphan*/ * channels; struct platform_device* pdev; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_mtu2_device*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int sh_mtu2_map_memory (struct sh_mtu2_device*) ; 
 int sh_mtu2_setup_channel (int /*<<< orphan*/ *,unsigned int,struct sh_mtu2_device*) ; 

__attribute__((used)) static int sh_mtu2_setup(struct sh_mtu2_device *mtu,
			 struct platform_device *pdev)
{
	unsigned int i;
	int ret;

	mtu->pdev = pdev;

	raw_spin_lock_init(&mtu->lock);

	/* Get hold of clock. */
	mtu->clk = clk_get(&mtu->pdev->dev, "fck");
	if (IS_ERR(mtu->clk)) {
		dev_err(&mtu->pdev->dev, "cannot get clock\n");
		return PTR_ERR(mtu->clk);
	}

	ret = clk_prepare(mtu->clk);
	if (ret < 0)
		goto err_clk_put;

	/* Map the memory resource. */
	ret = sh_mtu2_map_memory(mtu);
	if (ret < 0) {
		dev_err(&mtu->pdev->dev, "failed to remap I/O memory\n");
		goto err_clk_unprepare;
	}

	/* Allocate and setup the channels. */
	mtu->num_channels = 3;

	mtu->channels = kcalloc(mtu->num_channels, sizeof(*mtu->channels),
				GFP_KERNEL);
	if (mtu->channels == NULL) {
		ret = -ENOMEM;
		goto err_unmap;
	}

	for (i = 0; i < mtu->num_channels; ++i) {
		ret = sh_mtu2_setup_channel(&mtu->channels[i], i, mtu);
		if (ret < 0)
			goto err_unmap;
	}

	platform_set_drvdata(pdev, mtu);

	return 0;

err_unmap:
	kfree(mtu->channels);
	iounmap(mtu->mapbase);
err_clk_unprepare:
	clk_unprepare(mtu->clk);
err_clk_put:
	clk_put(mtu->clk);
	return ret;
}