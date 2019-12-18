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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct aspeed_video {int frame_rate; int /*<<< orphan*/  base; int /*<<< orphan*/ * dev; int /*<<< orphan*/  buffers; int /*<<< orphan*/  res_work; int /*<<< orphan*/  wait; int /*<<< orphan*/  video_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int aspeed_video_init (struct aspeed_video*) ; 
 int /*<<< orphan*/  aspeed_video_resolution_work ; 
 int aspeed_video_setup_video (struct aspeed_video*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct aspeed_video* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aspeed_video_probe(struct platform_device *pdev)
{
	int rc;
	struct resource *res;
	struct aspeed_video *video = kzalloc(sizeof(*video), GFP_KERNEL);

	if (!video)
		return -ENOMEM;

	video->frame_rate = 30;
	video->dev = &pdev->dev;
	spin_lock_init(&video->lock);
	mutex_init(&video->video_lock);
	init_waitqueue_head(&video->wait);
	INIT_DELAYED_WORK(&video->res_work, aspeed_video_resolution_work);
	INIT_LIST_HEAD(&video->buffers);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	video->base = devm_ioremap_resource(video->dev, res);

	if (IS_ERR(video->base))
		return PTR_ERR(video->base);

	rc = aspeed_video_init(video);
	if (rc)
		return rc;

	rc = aspeed_video_setup_video(video);
	if (rc)
		return rc;

	return 0;
}