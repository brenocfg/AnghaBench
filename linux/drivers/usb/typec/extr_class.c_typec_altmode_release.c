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
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct altmode {int /*<<< orphan*/  id; TYPE_2__ adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  altmode_id_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct altmode*) ; 
 struct altmode* to_altmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_typec_altmode (struct device*) ; 
 int /*<<< orphan*/  typec_altmode_put_partner (struct altmode*) ; 

__attribute__((used)) static void typec_altmode_release(struct device *dev)
{
	struct altmode *alt = to_altmode(to_typec_altmode(dev));

	typec_altmode_put_partner(alt);

	altmode_id_remove(alt->adev.dev.parent, alt->id);
	kfree(alt);
}