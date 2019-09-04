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
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxt_configure_objects (void*,struct firmware const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static void mxt_config_cb(const struct firmware *cfg, void *ctx)
{
	mxt_configure_objects(ctx, cfg);
	release_firmware(cfg);
}