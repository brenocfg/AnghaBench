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
struct qxl_drawable {int dummy; } ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QXL_RELEASE_DRAWABLE ; 
 int qxl_alloc_release_reserved (struct qxl_device*,int,int /*<<< orphan*/ ,struct qxl_release**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
alloc_drawable(struct qxl_device *qdev, struct qxl_release **release)
{
	return qxl_alloc_release_reserved(qdev, sizeof(struct qxl_drawable),
					  QXL_RELEASE_DRAWABLE, release, NULL);
}