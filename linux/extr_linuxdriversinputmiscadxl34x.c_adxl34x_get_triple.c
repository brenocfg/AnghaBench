#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct axis_triple {void* z; void* y; void* x; } ;
struct TYPE_4__ {void* z; void* y; void* x; } ;
struct adxl34x {int /*<<< orphan*/  mutex; TYPE_2__ saved; int /*<<< orphan*/  dev; TYPE_1__* bops; } ;
typedef  void* s16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_block ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,short*) ;} ;

/* Variables and functions */
 scalar_t__ DATAX0 ; 
 scalar_t__ DATAZ1 ; 
 scalar_t__ le16_to_cpu (short) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,short*) ; 

__attribute__((used)) static void adxl34x_get_triple(struct adxl34x *ac, struct axis_triple *axis)
{
	short buf[3];

	ac->bops->read_block(ac->dev, DATAX0, DATAZ1 - DATAX0 + 1, buf);

	mutex_lock(&ac->mutex);
	ac->saved.x = (s16) le16_to_cpu(buf[0]);
	axis->x = ac->saved.x;

	ac->saved.y = (s16) le16_to_cpu(buf[1]);
	axis->y = ac->saved.y;

	ac->saved.z = (s16) le16_to_cpu(buf[2]);
	axis->z = ac->saved.z;
	mutex_unlock(&ac->mutex);
}