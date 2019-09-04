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
struct ata_host {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ata_host_put(struct ata_host *host)
{
	kref_put(&host->kref, ata_host_release);
}