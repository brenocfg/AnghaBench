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
typedef  int /*<<< orphan*/  u32 ;
struct fw_iso_context {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int dummy_start_iso(struct fw_iso_context *ctx,
			   s32 cycle, u32 sync, u32 tags)
{
	return -ENODEV;
}