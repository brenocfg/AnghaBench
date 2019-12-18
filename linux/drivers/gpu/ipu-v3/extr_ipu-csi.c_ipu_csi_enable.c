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
struct ipu_csi {int /*<<< orphan*/  module; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_module_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipu_csi_enable(struct ipu_csi *csi)
{
	ipu_module_enable(csi->ipu, csi->module);

	return 0;
}