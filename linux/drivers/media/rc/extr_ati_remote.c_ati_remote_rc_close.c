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
struct rc_dev {struct ati_remote* priv; } ;
struct ati_remote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ati_remote_close (struct ati_remote*) ; 

__attribute__((used)) static void ati_remote_rc_close(struct rc_dev *rdev)
{
	struct ati_remote *ati_remote = rdev->priv;
	ati_remote_close(ati_remote);
}