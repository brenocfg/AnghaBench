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
struct venc_device {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  omapdss_device_cleanup_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omapdss_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void venc_uninit_output(struct venc_device *venc)
{
	omapdss_device_unregister(&venc->output);
	omapdss_device_cleanup_output(&venc->output);
}