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
struct mtk_jpeg_ctx {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MTK_JPEG_RUNNING ; 

__attribute__((used)) static int mtk_jpeg_job_ready(void *priv)
{
	struct mtk_jpeg_ctx *ctx = priv;

	return (ctx->state == MTK_JPEG_RUNNING) ? 1 : 0;
}