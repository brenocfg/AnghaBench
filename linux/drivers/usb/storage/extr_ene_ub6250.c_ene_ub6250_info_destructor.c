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
struct ene_ub6250_info {int /*<<< orphan*/  bbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ene_ub6250_info_destructor(void *extra)
{
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) extra;

	if (!extra)
		return;
	kfree(info->bbuf);
}