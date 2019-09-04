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
struct a6xx_hfi_msg_response {int dummy; } ;
struct a6xx_hfi_msg_error {int /*<<< orphan*/  code; } ;
struct a6xx_gmu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a6xx_hfi_handle_error(struct a6xx_gmu *gmu,
		struct a6xx_hfi_msg_response *msg)
{
	struct a6xx_hfi_msg_error *error = (struct a6xx_hfi_msg_error *) msg;

	dev_err(gmu->dev, "GMU firmware error %d\n", error->code);
}