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
struct delta_mjpeg_ctx {int dummy; } ;
struct delta_ctx {struct delta_mjpeg_ctx* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct delta_mjpeg_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delta_mjpeg_open(struct delta_ctx *pctx)
{
	struct delta_mjpeg_ctx *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	pctx->priv = ctx;

	return 0;
}