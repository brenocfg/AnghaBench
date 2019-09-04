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
struct drm_device {int /*<<< orphan*/  dev; struct ast_private* dev_private; } ;
struct ast_private {int /*<<< orphan*/  dp501_fw; } ;

/* Variables and functions */
 int request_firmware (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ast_load_dp501_microcode(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;

	return request_firmware(&ast->dp501_fw, "ast_dp501_fw.bin", dev->dev);
}