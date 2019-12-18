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
struct qxl_release {int dummy; } ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qxl_release_free (struct qxl_device*,struct qxl_release*) ; 

__attribute__((used)) static void
free_drawable(struct qxl_device *qdev, struct qxl_release *release)
{
	qxl_release_free(qdev, release);
}