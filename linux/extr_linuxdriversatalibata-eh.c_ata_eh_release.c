#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  eh_mutex; int /*<<< orphan*/ * eh_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ata_eh_release(struct ata_port *ap)
{
	WARN_ON_ONCE(ap->host->eh_owner != current);
	ap->host->eh_owner = NULL;
	mutex_unlock(&ap->host->eh_mutex);
}